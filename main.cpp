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

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char* argv[]) {

    //TODO
    //2. Update game loop so it doesn't use SDL functions 
    //   a. Add Input System (wait for event ststem in garch)
    //

    //Init Game
    Game::createInstance();
    Game::instnace()->init(SCREEN_WIDTH, SCREEN_HEIGHT, 60);

    // THE LOOP
    Game::instnace()->doLoop();

    //Cleanup
    Game::instnace()->cleanup();
    Game::removeInstance();

    //Print any leftover memory allocations
    MemoryTracker::instance()->printAllocations();

    //Quit
    SDL_Quit();

    return 0;
}
