#pragma once
#include "SDL3/SDL_render.h"
#include <iostream>

#include "Tracked.h"
#include "Vector2.h"
#include "Color.h"

class Sprite : public Tracked
{
public:
	Sprite(const std::string& filePath, const float& width, const float& height);
	~Sprite();

	SDL_Surface* getSurface() const { return mSurface; }
	unsigned int width() const { return mWidth; }
	unsigned int height() const { return mHeight; }
	Vector2 size() const { return Vector2(mWidth, mHeight); }

	void setColor(const Color& color) { mColor = color; }
	void draw(Vector2 position, float angle);

private:
	SDL_Surface* mSurface;
	SDL_Texture* mTexture;
	Color mColor;

	SDL_FRect mRect;
	SDL_FPoint mRectCenter;
	
	int mWidth;
	int mHeight;
};