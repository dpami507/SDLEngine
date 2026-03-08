#include "Game.h"

Game* Game::mpsInstance = nullptr;

//Create static instance
Game* Game::createInstance()
{
    mpsInstance = new Game();
    return mpsInstance;
}
//Get static instance
Game* Game::instnace()
{
    if (mpsInstance == nullptr)
    {
        createInstance();
    }

    return mpsInstance;
}
//Remove and cleanup static instance
void Game::removeInstance()
{
    delete mpsInstance;
    mpsInstance = nullptr;
}

//Initialize the Game
bool Game::init(const uint32_t& width, const uint32_t& height, const uint32_t& gameFPS)
{
    Debug::log(YELLOW) << "Initializing Game";

    //Set game variables
    mFPS = gameFPS;

    //Create manager
    mGameObjectManager = new GameObjectManager();
    mGraphicsSystem = new GraphicsSystem();

    bool init = mGraphicsSystem->init(width, height);

    if (init == true)
    {
        //It worked!
        mRunning = true;
        Debug::log(GREEN) << "Game Initialized";
        return true;
    }
    else
    {
        mRunning = false;
        Debug::error() << "Game Initialization Failed";
        return false;
    }
}

//Cleanup managers and Game
void Game::cleanup()
{
    //Clean up managers
    delete mGameObjectManager;
    mGameObjectManager = nullptr;

    delete mGraphicsSystem;
    mGraphicsSystem = nullptr;
}

Game::Game()
{
    
}

Game::~Game()
{
    cleanup();
}