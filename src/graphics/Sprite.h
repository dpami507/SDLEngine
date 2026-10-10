#pragma once
#include "SDL3/SDL_render.h"
#include <iostream>

#include "Tracked.h"
#include "Vector2.h"
#include "Color.h"

class GraphicsSystem;

class Sprite : public Tracked
{
public:
	Sprite(GraphicsSystem* graphicsSystem, const std::string& filePath, float width, float height);
	~Sprite();

	SDL_Surface* getSurface() const { return mSurface; }
	unsigned int width() const { return mWidth; }
	unsigned int height() const { return mHeight; }
	engine::math::Vector2 size() const { return engine::math::Vector2(mWidth, mHeight); }

	void setColor(const engine::color::Color& color) { mColor = color; }
	void draw(engine::math::Vector2 position, float angle);

private:
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;
	engine::color::Color mColor;

	GraphicsSystem* mGraphicsSystem;

	SDL_FRect mRect;
	SDL_FPoint mRectCenter;
	
	int mWidth;
	int mHeight;
};