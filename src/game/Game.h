#pragma once
#include "Tracked.h"

#include <iostream>

#include "GraphicsSystem.h"
#include "GameObjectManager.h"
#include "SoundManager.h"
#include "MemoryManager.h"
#include "EventSystem.h"
#include "InputTranslator.h"


static class Game : public EventListener
{
public:

	static Game* createInstance();
	static Game* instnace();
	static void removeInstance();

	//Getters
	inline GameObjectManager* getGameObjectManager() const { return mGameObjectManager; }
	inline engine::graphics::GraphicsSystem* getGraphicsSystem() const { return mGraphicsSystem; }
	inline engine::audio::SoundManager* getSoundManager() const { return mSoundManager; }
	inline engine::memory::MemoryManager* getMemoryManager() const { return mMemoryManager; }

	//time variables
	void setFPS(uint32_t FPS);
	inline uint32_t getFPS() const { return mFPS; }
	inline double getFrameLengthMS() const { return mTargetFrameLengthMS; }

	// event
	void handleEvent(const Event& event) override;

	// Game state 
	inline bool running() const { return mRunning; }
	inline void stop() { mRunning = false; }
	void doLoop();

	bool init(const uint32_t& width = 800, const uint32_t& height = 600, const uint32_t& gameFPS = 60);
	void cleanup();

private:
	Game();
	~Game();

	//Static instance
	static Game* mpsInstance;

	//Managers
	GameObjectManager* mGameObjectManager = nullptr;
	engine::graphics::GraphicsSystem* mGraphicsSystem = nullptr;
	engine::audio::SoundManager* mSoundManager = nullptr;
	engine::memory::MemoryManager* mMemoryManager = nullptr;
	InputTranslator* mInputTranslator = nullptr;

	//Game FPS
	uint32_t mFPS = 30;
	//Frame length in miliseconds
	double mTargetFrameLengthMS = 0;

	//Is the game running?
	bool mRunning = false;
};