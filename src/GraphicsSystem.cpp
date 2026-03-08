#include "GraphicsSystem.h"

GraphicsSystem::GraphicsSystem()
{
}

GraphicsSystem::~GraphicsSystem()
{
	cleanup();
}

/*
Initialize the Graphics System and SDL3
@return returns true if initialized
*/
bool GraphicsSystem::init(const uint32_t width, const uint32_t height)
{
	mScreenWidth = width;
	mScreenHeight = height;

	//Initialize SDL Video
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		Debug::error() << "Could not initialize SDL3: " << SDL_GetError();
		return false;
	}
	//Create Window
	mWindow = SDL_CreateWindow("My SDL3 Window", mScreenWidth, mScreenHeight, SDL_WINDOW_RESIZABLE);
	if (mWindow == NULL) {
		// Window could not be made...
		Debug::error() << "Could not create window: " << SDL_GetError();
		return false;
	}
	//Create Renderer
	mRenderer = SDL_CreateRenderer(mWindow, nullptr);
	if (mRenderer == NULL) {
		// Window could not be made...
		Debug::error() << "Could not create renderer: " << SDL_GetError();
		return false;
	}

	return true;
}
//Cleanup renderer and window
void GraphicsSystem::cleanup()
{
	//Destroy window and renderer
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

/*
*Clear the renderer to a color
@param Color to set screen to
*/ 
void GraphicsSystem::clearToColor(Color color)
{
	//Set color to draw
	SDL_SetRenderDrawColor(mRenderer, color.getRed(), color.getBlue(), color.getGreen(), color.getAlpha());
	//Clear the renderer with the color we just set
	SDL_RenderClear(mRenderer);
}
//Flips the graphics system
void GraphicsSystem::flip()
{
	//Esetially a flip() function, takes the renderer and draws it
	SDL_RenderPresent(mRenderer);
}