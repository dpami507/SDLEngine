#include "SoundManager.h"
#include "Debug.h"

#include "MemoryManager.h"

SoundManager::~SoundManager()
{
    cleanup();
}

bool SoundManager::init(MemoryManager* memoryManager)
{
    // Init SDL Audio
    if (!SDL_Init(SDL_INIT_AUDIO))
    {
        engine::Debug::error() << "SDL Audio could not be loaded!";
        return false;
    }

    mMemoryManager = memoryManager;

    // Create Loaded Audio
    mSpec = new SDL_AudioSpec();
    mSpec->channels = 2;
    mSpec->format = SDL_AUDIO_F32;
    mSpec->freq = 44100;

    for (int i = 0; i < STREAM_COUNT; i++)
    {
        // Create the Audio Stream
        mStreams[i] = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, mSpec, NULL, NULL);
        if (!mStreams) {
            engine::Debug::error() << "Couldn't create audio stream: " << SDL_GetError();
            return false;
        }
        // Unpause the stream
        SDL_ResumeAudioStreamDevice(mStreams[i]);
    }

    engine::Debug::log(engine::DBG_BLUE, "[INIT]") << "Sound Manager Inititialized";
    return true;
}
void SoundManager::cleanup()
{
    engine::Debug::log(engine::DBG_YELLOW, "[CLEANUP]") << "Cleaning up Sound Manager";

    // Cleanup loaded audio
    for (auto a : mLoadedAudio)
    {
        SDL_free(a.second->sWavData);
        mMemoryManager->deallocate((Byte*)a.second);
    }
    mLoadedAudio.clear();

    // Cleanup streams
    for (auto& s : mStreams)
    {
        if (s != nullptr)
        {
            SDL_DestroyAudioStream(s);
            s = nullptr;
        }
    }
}

bool SoundManager::loadAudio(std::string key, std::string path)
{
    // Check for audio
    if (mLoadedAudio.find(key) != mLoadedAudio.end())
    {
        engine::Debug::error() << "Key: " << key << " already exists!";
        return false;
    }

    // Create Loaded Audio
    Byte* allocByte = mMemoryManager->allocate(sizeof(LoadedAudio));
    if (allocByte == nullptr) return false;

    LoadedAudio* newAudio = new (allocByte) LoadedAudio();

    // Load the file
    if (!SDL_LoadWAV(path.c_str(), &newAudio->sSpec, &newAudio->sWavData, &newAudio->sLength))
    {
        engine::Debug::error() << "Failed to load audio path: " << path << ": " << SDL_GetError();
        return false;
    }

    // Insert
    mLoadedAudio.insert({ key, newAudio });
    return true;
}
bool SoundManager::playAudio(std::string key)
{
    // Make sure the key is real
    auto it = mLoadedAudio.find(key);
    if (it == mLoadedAudio.end())
    {
        engine::Debug::error() << "Key: " << key << " wasn't found!";
        return false;
    }

    // Load Audio and put it into the stream
    LoadedAudio* audio = it->second;

    // Convert the WAV
    uint8_t* convertedBuffer = nullptr;
    int convertedLength = 0;
    if (!SDL_ConvertAudioSamples(&audio->sSpec, audio->sWavData, audio->sLength, mSpec, &convertedBuffer, &convertedLength))
    {
        engine::Debug::error() << "Audio conversion failed: " << SDL_GetError();
        return false;
    }

    SDL_AudioStream* stream = getAvailableStream();
    if (stream != nullptr)
    {
        SDL_PutAudioStreamData(stream, convertedBuffer, convertedLength);

        SDL_free(convertedBuffer);

        return true;
    }

    SDL_free(convertedBuffer);
    return false;
}

SDL_AudioStream* SoundManager::getAvailableStream()
{
    for (int i = 0; i < STREAM_COUNT; i++)
    {
        if (SDL_GetAudioStreamAvailable(mStreams[i]) == 0)
        {
            return mStreams[i];
        }
    }

    engine::Debug::error() << "All audio streams are in use!";
    return nullptr;
}