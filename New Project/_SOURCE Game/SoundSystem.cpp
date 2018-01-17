#include <assert.h>

#include "../_SOURCE Game/SoundSystem.h"
#pragma comment (lib, "xaudio2.lib")

SoundSystem& SoundSystem::Get()
{
	static SoundSystem instance;
	return instance;
}

SoundSystem::SoundSystem()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	XAudio2Create(&pEngine);
	pEngine->CreateMasteringVoice(&pMaster);
	for (int i = 0; i < nChannels; i++)
	{
		idleChannelPtrs.push_back(std::make_unique<Channel>(*this));
	}
}

void SoundSystem::Channel::VoiceCallback::OnBufferEnd(void* pBufferContext)
{
	Channel& chan = *(Channel*)pBufferContext;
	chan.Stop();
	chan.pSound->RemoveChannel(chan);
	chan.pSound = nullptr;
	SoundSystem::Get().DeactivateChannel(chan);
}

void SoundSystem::Channel::PlaySoundBuffer(Sound& s, float freqMod, float vol)
{
	static VoiceCallback vcb;
	pSys->pEngine->CreateSourceVoice(&pSource, &s.wfx, 0U, 2.0f, &vcb);
	assert(pSource && !pSound);
	s.AddChannel(*this);
	// callback thread not running yet, so no sync necessary for pSound
	
	pSound = &s;
	xaBuffer.pAudioData = s.pData;
	xaBuffer.AudioBytes = s.nBytes;
	pSource->SubmitSourceBuffer(&xaBuffer, nullptr);
	pSource->SetFrequencyRatio(freqMod);
	pSource->SetVolume(vol);
	pSource->Start();
}
