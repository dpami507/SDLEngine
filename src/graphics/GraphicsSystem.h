#include "SDL3/SDL_render.h"
#include "SDL3/SDL_init.h"

#include "Tracked.h"
#include "Debug.h"
#include "Color.h"

class GraphicsSystem : public Tracked
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	bool init(const uint32_t width, const uint32_t height);
	void cleanup();

	inline uint32_t getWindowHeight() const { return mScreenHeight; };
	inline uint32_t getWindowWidth() const { return mScreenWidth; };

	void clearToColor(const engine::color::Color& color);
	void flip();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	friend class Sprite;
	SDL_Window* getWindow() { return mWindow; }
	SDL_Renderer* getRenderer() { return mRenderer; }

	uint32_t mScreenWidth;
	uint32_t mScreenHeight;
};