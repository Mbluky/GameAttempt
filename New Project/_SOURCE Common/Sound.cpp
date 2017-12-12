#include "Sound.h"

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif


SoundSystem & SoundSystem::Get()
{
	static SoundSystem instance;
	return instance;
}

IXAudio2 * SoundSystem::getAudioInterface()
{
	return xAudioInterface;
}

XAUDIO2_VOICE_SENDS SoundSystem::getVoiceSends(bool isSFX)
{
	if(isSFX)
		return SendListSFX;
	else
		return SendListMusic;
}

SoundSystem::~SoundSystem()
{
	xAudioInterface->Release();
	delete xAudioMasteringVoice;
	delete pMusicSubmixVoice;
	delete pSoundEffectsSubmixVoice;
}


SoundSystem::SoundSystem()
{
	HRESULT hr;
	hr = XAudio2Create(&xAudioInterface, 0, XAUDIO2_DEFAULT_PROCESSOR);

	hr = xAudioInterface->CreateMasteringVoice(&xAudioMasteringVoice);

	xAudioInterface->CreateSubmixVoice(&pMusicSubmixVoice, 1, 44100, 0, 0, 0, 0);
	xAudioInterface->CreateSubmixVoice(&pSoundEffectsSubmixVoice, 1, 44100, 0, 0, 0, 0);
	

	XAUDIO2_SEND_DESCRIPTOR SFXSendMusic = { 0, pMusicSubmixVoice };
	SendListMusic = { 1, &SFXSendMusic };

	XAUDIO2_SEND_DESCRIPTOR SFXSendSFX = { 0, pSoundEffectsSubmixVoice };
	SendListSFX = { 1, &SFXSendSFX };

}

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}

	return S_OK;

}
HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}

soundEffect::soundEffect(TCHAR * strFileName, bool isSFX)
{
	//source audio -> Source voice -> submix -> master voice
	HRESULT hr = S_OK;
	m_isSFX = isSFX;

	HANDLE hFile = CreateFile(
		strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	//if file type is not fourccWave, set exeption here

	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE * pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

	buffer.AudioBytes = dwChunkSize;
	buffer.pAudioData = pDataBuffer;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	VoiceCallback* pCallback;
	//set up exeption here
	for (int x = 0; x == 20; x++)
	{
		if (SoundChannelList[x].sourceVoice == NULL)
		{
			hr = SoundSystem::Get().getAudioInterface()->CreateSourceVoice(&SoundChannelList[x].sourceVoice, (WAVEFORMATEX*)&wfx,
				0, XAUDIO2_DEFAULT_FREQ_RATIO, pCallback, &SoundSystem::Get().getVoiceSends(isSFX), NULL);
			//set exeption here
			hr = SoundChannelList[x].sourceVoice->SubmitSourceBuffer(&buffer);
			//set exception here
		}
	}
}

void soundEffect::playSound()
{
	for(int x = 0; x == 20; x++)
	{
		if(!SoundChannelList[x].isActive)
		{
			SoundChannelList[x].sourceVoice->Start();
			break;
		}
	}
}
