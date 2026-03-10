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

	//Setters
	void stop() { mRunning = false; }

	//Getters
	GameObjectManager* getGameObjectManager() { return mGameObjectManager; }
	GraphicsSystem* getGraphicsSystem() { return mGraphicsSystem; }
	SoundManager* getSoundManager() { return mSoundManager; }

	uint32_t getFPS() { return mFPS; }
	void setFPS(uint32_t FPS);
	double getFrameLengthMS() { return mTargetFrameLengthMS; }
	double getDeltaTime() { return mDeltaTime; }
	double getElapsedTime() { return mGameTimer->getElapsedTime(); }

	bool running() const { return mRunning; }

	bool init(const uint32_t& width = 800, const uint32_t& height = 600, const uint32_t& gameFPS = 60);
	void cleanup();

private:
	Game();
	~Game();

	//Static instance
	static Game* mpsInstance;

	//Managers
	GameObjectManager* mGameObjectManager;
	GraphicsSystem* mGraphicsSystem;
	SoundManager* mSoundManager;

	//Game FPS
	uint32_t mFPS;
	//Frame length in miliseconds
	double mTargetFrameLengthMS;
	//Delta Time
	double mDeltaTime;
	//Time
	Timer* mGameTimer;

	//Is the game running?
	bool mRunning;
};