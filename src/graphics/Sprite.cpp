#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(const std::string& filePath, const float& width, const float& height)
{
	//Set width and height
	mWidth = width;
	mHeight = height;

	//Load image and create texture
	mSurface = SDL_LoadPNG(filePath.c_str());
	mTexture = SDL_CreateTextureFromSurface(Game::instnace()->getGraphicsSystem()->getRenderer(), mSurface);

	//Create rect it will go on
	mRect = { 0, 0, width, height };
	mRectCenter = { width / 2, height / 2 };
}
Sprite::~Sprite()
{
	//If there is a surface kill it
	if(mSurface != nullptr)
		SDL_DestroySurface(mSurface);
	//If there is a texture kill it
	if (mTexture != nullptr)
		SDL_DestroyTexture(mTexture);
}

/*
Draw to the renderer
@param position: where to draw it
@param angle: rotation of sprite
*/
void Sprite::draw(Vector2 position, float angle)
{
	mRect.x = position.x;
	mRect.y = position.y;

	//Set color mod
	SDL_SetTextureColorMod(mTexture, mColor.getRed(), mColor.getGreen(), mColor.getBlue());

	//Draw texture to renderer
	SDL_RenderTextureRotated(Game::instnace()->getGraphicsSystem()->getRenderer(), mTexture, NULL, &mRect, angle, &mRectCenter, SDL_FLIP_NONE);
}