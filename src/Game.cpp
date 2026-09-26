#include "Game.h"

#include "Timer.h"
#include "DeltaTime.h"

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
    engine::Debug::warning() << "Initializing Game";

    //Set game variables
    setFPS(gameFPS);

    //Create manager
    mGameObjectManager = new GameObjectManager();
    mGraphicsSystem = new GraphicsSystem();
    mSoundManager = new SoundManager();
    mMemoryManager = new MemoryManager();

    bool init = true;
    init &= mGraphicsSystem->init(width, height);
    init &= mGameObjectManager->init();
    init &= mSoundManager->init();
    init &= mMemoryManager->init({ 32 }, { 1 });

    if (init == true)
    {
        //It worked!
        mRunning = true;
        engine::Debug::success() << "Game Initialized";
        return true;
    }
    else
    {
        mRunning = false;
        engine::Debug::error() << "Game Initialization Failed";
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

    delete mSoundManager;
    mSoundManager = nullptr;

    delete mMemoryManager;
    mMemoryManager = nullptr;
}

void Game::doLoop()
{
    //Load sounds
    Game::instnace()->getSoundManager()->loadClip("explosion", "resources/boom_x.wav");

    //Create player
    Sprite* sprite = new Sprite("resources/dvd.png", 125, 58);
    GameObject* player = Game::instnace()->getGameObjectManager()->instantiate();
    player->setSprite(sprite);

    //Square variables
    Vector2 dir = Vector2(1, 1);

    player->transform.position = Vector2(10, 10);

    //Keep speed the same for all fps
    double speed = 450;

    //Get array of keys and their state
    const bool* keys = SDL_GetKeyboardState(nullptr);

    //Create Timer
    Timer frameTimer;
    DeltaTime deltaTime;

    deltaTime.start();
    while (Game::instnace()->running()) {
        SDL_Event event;

        //Start timer
        frameTimer.start();
        deltaTime.update();

        //Clear the screen to a color
        Game::instnace()->getGraphicsSystem()->clearToColor({ 0, 0, 0, 255 });

        //Wait for events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                engine::Debug::warning() << "Quiting...";
                Game::instnace()->stop();
            }
            //Debug which key was pressed down
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                engine::Debug::log() << "a key was pressed: " << event.key.key;
            }
        }
        //Stop if we hit the escape button
        if (keys[SDL_SCANCODE_ESCAPE])
            Game::instnace()->stop();

        //Change direction if we hit a wall
        if (player->transform.position.y > mGraphicsSystem->getWindowHeight() - player->sprite()->height())
        {
            dir.y = -1;
            player->sprite()->setColor(Color::getRandColor());
            Game::instnace()->getSoundManager()->playClip("explosion");
        }
        if (player->transform.position.x > mGraphicsSystem->getWindowWidth() - player->sprite()->width())
        {
            dir.x = -1;
            player->sprite()->setColor(Color::getRandColor());
            Game::instnace()->getSoundManager()->playClip("explosion");
        }
        if (player->transform.position.y < 0)
        {
            dir.y = 1;
            player->sprite()->setColor(Color::getRandColor());
            Game::instnace()->getSoundManager()->playClip("explosion");
        }
        if (player->transform.position.x < 0)
        {
            dir.x = 1;
            player->sprite()->setColor(Color::getRandColor());
            Game::instnace()->getSoundManager()->playClip("explosion");
        }

        //take the normalized direction and multiply it by the speed
        player->transform.position += dir.normalized() * speed * deltaTime.get();

        //Update then draw player
        player->update();
        player->draw();

        //flip
        Game::instnace()->getGraphicsSystem()->flip();

        //Sleep until end of frame length
        frameTimer.sleepUntilElapsed(Game::instnace()->getFrameLengthMS());
    }
}

void Game::setFPS(uint32_t FPS)
{
    mFPS = FPS;
    mTargetFrameLengthMS = 1000.0 / FPS;
}

Game::Game()
{
    
}

Game::~Game()
{
    cleanup();
}