#include "SDL3/SDL_render.h"
#include "SDL3/SDL_init.h"

#include "Tracked.h"
#include "Debug.h"

class GraphicsSystem : public Tracked
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	bool init(const uint32_t width, const uint32_t height);
	void cleanup();

	SDL_Window* getWindow() { return mWindow; }
	SDL_Renderer* getRenderer() { return mRenderer; }

	void clearToColor();
	void flip();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	uint32_t mScreenWidth;
	uint32_t mScreenHeight;
};