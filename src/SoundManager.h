#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_init.h"
#include "SDL3_mixer/SDL_mixer.h"

#include <unordered_map>

#include "Debug.h"
#include "Tracked.h"

struct AudioClip : public Tracked
{
	MIX_Audio* audio;
	double vol;
	double pitch;
};

class SoundManager : public Tracked
{
public:
	SoundManager();
	~SoundManager();

	bool init();
	void cleanup();

	bool loadClip(const std::string key, const std::string filename);
	bool playClip(const std::string key);
	void cleanupTracks();
	void purgeTracks();

private:
	MIX_Mixer* mMixer;
	std::vector<MIX_Track*> mActiveTracks;
	std::unordered_map<std::string, AudioClip*> mAudioClips;
};