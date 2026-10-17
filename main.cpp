#include <SDL3/SDL.h>
#include <iostream>
#include <cassert>

#include "Game.h"
#include "Vector2.h"
#include "Sprite.h"
#include "GameObject.h"
#include "MemoryTracker.h"
#include "Timer.h"
#include "Debug.h"
#include "DeltaTime.h"
#include "EventSystem.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {

    //TODO
    //2. Update game loop so it doesn't use SDL functions 
    //   a. Add Input System (wait for event ststem in garch)
    //

    // Init Events
    EventSystem::createInstance();
    EventSystem::instance()->init();

    //Init Game
    Game::createInstance();
    Game::instnace()->init(SCREEN_WIDTH, SCREEN_HEIGHT, 60);


    // THE LOOP
    Game::instnace()->doLoop();

    //Cleanup
    Game::removeInstance();
    EventSystem::removeInstance();

    //Print any leftover memory allocations
    engine::memory::MemoryTracker::instance()->printAllocations();

    //Quit
    SDL_Quit();

    return 0;
}
