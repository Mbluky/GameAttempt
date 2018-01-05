#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

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

#include <assert.h>
#include <xaudio2.h>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <vector>
#include <mutex>
#include <atomic>
#include <wrl\client.h>

class SoundSystem
{
public:
	class Error : public std::runtime_error
	{
	public:
		Error(std::string s)
			:
			runtime_error(std::string("SoundSystem::Error: ") + s)
		{}
	};
	class FileError : public Error
	{
	public:
		FileError(std::string s)
			:
			Error(std::string("SoundSystem::FileError: ") + s)
		{}
	};
public:
	class Channel
	{
	private:
		class VoiceCallback : public IXAudio2VoiceCallback
		{
		public:
			void STDMETHODCALLTYPE OnStreamEnd() override
			{}
			void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override
			{}
			void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired) override
			{}
			void STDMETHODCALLTYPE OnBufferEnd(void* pBufferContext) override;
			void STDMETHODCALLTYPE OnBufferStart(void* pBufferContext) override
			{}
			void STDMETHODCALLTYPE OnLoopEnd(void* pBufferContext) override
			{}
			void STDMETHODCALLTYPE OnVoiceError(void* pBufferContext, HRESULT Error) override
			{}
		};
	public:
		Channel(SoundSystem& sys)
		{
			ZeroMemory(&xaBuffer, sizeof(xaBuffer));
			xaBuffer.pContext = this;
			pSys = &sys;
		}
		Channel(const Channel&) = delete;
		~Channel()
		{
			assert(!pSound);
			if (pSource)
			{
				pSource->DestroyVoice();
				pSource = nullptr;
			}
		}
		void PlaySoundBuffer(class Sound& s, float freqMod, float vol);
		void Stop()
		{
			assert(pSource && pSound);
			pSource->Stop();
			pSource->FlushSourceBuffers();
		}
	private:
		XAUDIO2_BUFFER xaBuffer;
		IXAudio2SourceVoice* pSource = nullptr;
		// does this need to be synchronized?
		// (no--no overlap of callback thread and main thread here)
		class Sound* pSound = nullptr;
		class SoundSystem* pSys = nullptr;
	};
public:
	SoundSystem(const SoundSystem&) = delete;
	static SoundSystem& Get();
	static WAVEFORMATEX& GetFormat()
	{
		return Get().format;
	}
	void PlaySoundBuffer(class Sound& s, float freqMod, float vol)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (idleChannelPtrs.size() > 0)
		{
			activeChannelPtrs.push_back(std::move(idleChannelPtrs.back()));
			idleChannelPtrs.pop_back();
			activeChannelPtrs.back()->PlaySoundBuffer(s, freqMod, vol);
		}
	}
private:
	SoundSystem();
	void DeactivateChannel(Channel& channel)
	{
		std::lock_guard<std::mutex> lock(mutex);
		auto i = std::find_if(activeChannelPtrs.begin(), activeChannelPtrs.end(),
			[&channel](const std::unique_ptr<Channel>& pChan) -> bool
		{
			return &channel == pChan.get();
		});
		idleChannelPtrs.push_back(std::move(*i));
		activeChannelPtrs.erase(i);
	}
private:
	Microsoft::WRL::ComPtr<IXAudio2> pEngine;
	IXAudio2MasteringVoice* pMaster = nullptr;
	WAVEFORMATEX format;
	const int nChannels = 64;
	std::mutex mutex;
	std::vector<std::unique_ptr<Channel>> idleChannelPtrs;
	std::vector<std::unique_ptr<Channel>> activeChannelPtrs;
};

class Sound
{
	friend SoundSystem::Channel;
public:
	Sound(TCHAR * strFileName)
	{
		// Open the file
		HANDLE hFile = CreateFile(
			strFileName,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			0,
			NULL);
		SetFilePointer(hFile, 0, NULL, FILE_BEGIN);

		DWORD dwChunkSize;
		DWORD dwChunkPosition;
		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		DWORD filetype;
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		BYTE * pDataBuffer = new BYTE[dwChunkSize];
		ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);

		nBytes = dwChunkSize;  //buffer containing audio data
		pData = pDataBuffer;  //size of the audio buffer in bytes
	}
	Sound(const Sound&) = delete;
	Sound(Sound&& donor)
		:
		nBytes(donor.nBytes),
		pData(std::move(donor.pData)),
		activeChannelPtrs(std::move(donor.activeChannelPtrs))
	{}
	void Play(float freqMod, float vol)
	{
		SoundSystem::Get().PlaySoundBuffer(*this, freqMod, vol);
	}
	~Sound()
	{
		{
			std::lock_guard<std::mutex> lock(mutex);
			for (auto pChannel : activeChannelPtrs)
			{
				pChannel->Stop();
			}
		}

		bool allChannelsDeactivated = false;
		do
		{
			std::lock_guard<std::mutex> lock(mutex);
			allChannelsDeactivated = activeChannelPtrs.size() == 0;
		} while (!allChannelsDeactivated);
	}
private:
	void RemoveChannel(SoundSystem::Channel& channel)
	{
		std::lock_guard<std::mutex> lock(mutex);
		activeChannelPtrs.erase(std::find(
			activeChannelPtrs.begin(), activeChannelPtrs.end(), &channel));
	}
	void AddChannel(SoundSystem::Channel& channel)
	{
		std::lock_guard<std::mutex> lock(mutex);
		activeChannelPtrs.push_back(&channel);
	}
private:
	WAVEFORMATEX wfx = { 0 };
	UINT32 nBytes = 0;
	BYTE * pData = NULL;
	std::mutex mutex;
	std::vector<SoundSystem::Channel*> activeChannelPtrs;
private:
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

};

#endif // !SOUND_SYSTEM_H