#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_audio.h>

#include <iostream>
#include <string>
#include <unordered_map>

#include "Tracked.h"

namespace engine::memory { class MemoryManager; };

namespace engine::audio
{
    const int STREAM_COUNT = 8;

    class SoundManager : public engine::memory::Tracked
    {
    public:
        SoundManager() = default;
        ~SoundManager();

        bool init(engine::memory::MemoryManager* memoryManager);
        void cleanup();

        bool playAudio(std::string key);
        bool loadAudio(std::string key, std::string path);

        static inline uint8_t getAudioSizeof() { return sizeof(LoadedAudio); }

    private:
        struct LoadedAudio
        {
            uint8_t* sWavData;
            uint32_t sLength;
            SDL_AudioSpec sSpec;
        };

        SDL_AudioStream* getAvailableStream();

        std::unordered_map<std::string, LoadedAudio*> mLoadedAudio;
        SDL_AudioStream* mStreams[STREAM_COUNT];
        SDL_AudioSpec* mSpec = nullptr;

        engine::memory::MemoryManager* mMemoryManager = nullptr;
    };
}