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
		MIX_DestroyAudio(c.second->audio);
		delete c.second;
	}
	mAudioClips.clear();

	//Cleanup tracks
	purgeTracks();

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
bool SoundManager::playClip(const std::string key)
{
	//Cleanup any tracks
	cleanupTracks();

	//Make sure it exists
	auto it = mAudioClips.find(key);
	if (it == mAudioClips.end()) {
		Debug::error() << key << " doesn't exist!";
		return false;
	}

	//Get the clip
	AudioClip clip = *mAudioClips.at(key);

	//Create the track and add it to the vecotr
	MIX_Track* track = MIX_CreateTrack(mMixer);
	mActiveTracks.push_back(track);

	//Set up audio
	MIX_SetTrackAudio(track, clip.audio);

	//Play audio
	MIX_PlayTrack(track, 1);

	return true;
}

void SoundManager::cleanupTracks()
{
	mActiveTracks.erase(
		std::remove_if(mActiveTracks.begin(), mActiveTracks.end(),
		[](MIX_Track* track) {
			if (!MIX_TrackPlaying(track))
			{
				MIX_DestroyTrack(track);
				return true;
			}
			return false;
		}),
		mActiveTracks.end()
	);
}
void SoundManager::purgeTracks()
{
	//delete all and set null
	for (auto t : mActiveTracks)
		MIX_DestroyTrack(t);
}

