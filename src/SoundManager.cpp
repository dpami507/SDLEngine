#include "SoundManager.h"

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	cleanup();
}

bool SoundManager::init()
{
	//Init SDL Audio
	if (SDL_Init(SDL_INIT_AUDIO) == false)
	{
		Debug::error() << "Could not initialize SDL Audio: " << SDL_GetError();
		return false;
	}
	//Init SDL Mixer
	if(MIX_Init() == false)
	{
		Debug::error() << "Could not initialize SDL_mixer: " << SDL_GetError();
		return false;
	}
	//Create a mixer
	mMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
	if (mMixer == nullptr)
	{
		Debug::error() << "Could not create a mixer: " << SDL_GetError();
		return false;
	}

	Debug::log(DebugColor::CYAN, "[INIT]") << "Sound Manger Inititialized";
	return true;
}

void SoundManager::cleanup()
{
	//Destroy all clips
	for (auto c : mAudioClips)
	{
		delete c.second;
	}
	mAudioClips.clear();

	//Destroy the mixer
	MIX_DestroyMixer(mMixer);

	MIX_Quit();
}

//Load clip to the manager
bool SoundManager::loadClip(const std::string key, const std::string filename)
{
	//Make sure it doesnt exits
	auto it = mAudioClips.find(key);
	if (it != mAudioClips.end()) {
		Debug::error() << key << " already exists!";
		return false;
	}

	AudioClip* newClip = new AudioClip();

	//Load WAV file
	newClip->audio = MIX_LoadAudio(mMixer, filename.c_str(), true);
	if (newClip->audio == nullptr) {
		Debug::error() << "Failed to load WAV: " << SDL_GetError();
	}

	//Add to audio clips
	mAudioClips.insert({ key, newClip });

	return true;
}

//Play clip from loaded clip
bool SoundManager::playClip(std::string key)
{
	//Make sure it exists
	auto it = mAudioClips.find(key);
	if (it == mAudioClips.end()) {
		Debug::error() << key << " doesn't exist!";
		return false;
	}

	//Play it
	MIX_PlayAudio(mMixer, mAudioClips.at(key)->audio);

	return true;
}

