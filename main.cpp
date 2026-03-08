#include <SDL3/SDL.h>
#include <iostream>
#include <cassert>

#include "src/Game.h"
#include "src/Vector2.h"
#include "src/Sprite.h"
#include "src/GameObject.h"
#include "src/MemoryTracker.h"
#include "src/Timer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {

    //TODO
    //1. Add frame waiting so time is constant
    //2. Update game loop so it doesn't use SDL functions 
    //   a. Add Input System (wait for event ststem in garch)
    //

    //Init Game
    Game::createInstance();
    Game::instnace()->init(SCREEN_WIDTH, SCREEN_HEIGHT, 60);

    //Create Timer
    Timer timer;

    //Create player
    Sprite* sprite = new Sprite("resources/dvd.png", 125, 58);
    GameObject* player = Game::instnace()->getGameObjectManager()->instantiate();
    player->setSprite(sprite);

    //Square variables
    Vector2 dir = Vector2(1, 1);
    float speed = 3; //3 Pixels per frame

    //Get array of keys and their state
    const bool* keys = SDL_GetKeyboardState(nullptr);

    while (Game::instnace()->running()) {
        SDL_Event event;

        //Start timer
        timer.start();

        //Clear the screen to a color
        Game::instnace()->getGraphicsSystem()->clearToColor({0, 0, 0, 255});

        //Wait for events
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                Debug::warning() << "Quiting...";
                Game::instnace()->stop();
            }
            //Debug which key was pressed down
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                Debug::log() << "a key was pressed: " << event.key.key;
            }
        }
        //Stop if we hit the escape button
        if (keys[SDL_SCANCODE_ESCAPE])
            Game::instnace()->stop();

        //Change direction if we hit a wall
        if (player->transform.position.y > SCREEN_HEIGHT - player->sprite()->height())
        {
            dir.y = -1;
            player->sprite()->setColor(Color::getRandColor());
        }
        if (player->transform.position.x > SCREEN_WIDTH - player->sprite()->width())
        {
            dir.x = -1;
            player->sprite()->setColor(Color::getRandColor());
        }
        if (player->transform.position.y < 0)
        {
            dir.y = 1;
            player->sprite()->setColor(Color::getRandColor());
        }
        if (player->transform.position.x < 0)
        {
            dir.x = 1;
            player->sprite()->setColor(Color::getRandColor());
        }

        //take the normalized direction and multiply it by the speed
        player->transform.position += dir.normalized() * speed;

        //Update then draw player
        player->update();
        player->draw();

        //flip
        Game::instnace()->getGraphicsSystem()->flip();

        timer.sleepUnitl(Game::instnace()->getTargetFrameLengthMS());
        Debug::log(BLUE, "[TIME]") << timer.getElapsedTime();
    }

    //Cleanup
    Game::instnace()->cleanup();
    Game::removeInstance();

    //Print any leftover memory allocations
    MemoryTracker::instance()->printAllocations();

    //Quit
    SDL_Quit();

    return 0;
}
