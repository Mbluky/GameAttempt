#ifndef SOUND_XAUDIO2_HEADER
#define SOUND_XAUDIO2_HEADER

#include <xaudio2.h>

struct SOUNDCHANNEL
{
	IXAudio2SourceVoice* sourceVoice = NULL;
	bool isActive = false;
};

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	HANDLE hBufferEndEvent;
	VoiceCallback() : hBufferEndEvent(CreateEvent(NULL, FALSE, FALSE, NULL)) {}
	~VoiceCallback() { CloseHandle(hBufferEndEvent); }

	//Called when the voice has just finished playing a contiguous audio stream.
	void STDMETHODCALLTYPE OnStreamEnd() override { }

	//Unused methods are stubs
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() override { }
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32 SamplesRequired) override {    }
	void STDMETHODCALLTYPE OnBufferEnd(void * pBufferContext) override { }
	void STDMETHODCALLTYPE OnBufferStart(void * pBufferContext) override {    }
	void STDMETHODCALLTYPE OnLoopEnd(void * pBufferContext) override {    }
	void STDMETHODCALLTYPE OnVoiceError(void * pBufferContext, HRESULT Error)override { }
};

class SoundSystem
{
private:
	IXAudio2* xAudioInterface;
	IXAudio2MasteringVoice* xAudioMasteringVoice;
	IXAudio2SubmixVoice* pMusicSubmixVoice;
	IXAudio2SubmixVoice* pSoundEffectsSubmixVoice;
	XAUDIO2_VOICE_SENDS SendListSFX;
	XAUDIO2_VOICE_SENDS SendListMusic;
	unsigned int masterVolume, sfxVolume, musicVolume;
public:
	static SoundSystem& Get();
	IXAudio2* getAudioInterface();
	XAUDIO2_VOICE_SENDS getVoiceSends(bool isSFX);
	~SoundSystem();
private:
	SoundSystem();
};

HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);


class soundEffect
{
	SOUNDCHANNEL SoundChannelList[20];
	WAVEFORMATEXTENSIBLE wfx = { 0 };
	XAUDIO2_BUFFER buffer = { 0 };
	bool m_isSFX;
public:
	soundEffect(TCHAR * strFileName, bool isSFX);
	void playSound();
};
#endif // !SOUND_XAUDIO2_HEADER