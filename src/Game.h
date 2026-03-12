#pragma once
#include <iostream>

#include "Tracked.h"
#include "GameObjectManager.h"
#include "GraphicsSystem.h"
#include "SoundManager.h"
#include "Timer.h"

static class Game : public Tracked
{
public:

	static Game* createInstance();
	static Game* instnace();
	static void removeInstance();

	//Getters
	GameObjectManager* getGameObjectManager() { return mGameObjectManager; }
	GraphicsSystem* getGraphicsSystem() { return mGraphicsSystem; }
	SoundManager* getSoundManager() { return mSoundManager; }

	//Set time variables
	void setFPS(uint32_t FPS);
	void updateDeltaTime();

	//Get time variables
	uint32_t getFPS() { return mFPS; }
	double getFrameLengthMS() { return mTargetFrameLengthMS; }
	double getDeltaTime() { return mDeltaTime; }
	double getElapsedTime() { return mGameTimer->getElapsedTime(); }

	bool running() const { return mRunning; }
	void stop() { mRunning = false; }

	bool init(const uint32_t& width = 800, const uint32_t& height = 600, const uint32_t& gameFPS = 60);
	void cleanup();

private:
	Game();
	~Game();

	//Static instance
	static Game* mpsInstance;

	//Managers
	GameObjectManager* mGameObjectManager = nullptr;
	GraphicsSystem* mGraphicsSystem = nullptr;
	SoundManager* mSoundManager = nullptr;

	//Game FPS
	uint32_t mFPS = 30;
	//Frame length in miliseconds
	double mTargetFrameLengthMS = 0;

	//Time
	Timer* mGameTimer = nullptr;

	//Delta Time
	double mDeltaTime = 0;
	double mLastFrameTime = 0;

	//Is the game running?
	bool mRunning = false;
};