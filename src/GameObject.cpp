#include "GameObject.h"

GameObject::GameObject()
{
	mSprite = nullptr;
	transform.position = Vector2::zero();
	transform.rotationAngle = 0;
}
GameObject::~GameObject()
{
	if (mSprite != nullptr)
	{
		delete mSprite;
		mSprite = nullptr;
	}
}
//Update gameObject
void GameObject::update()
{

}
//Draw gameObject
void GameObject::draw()
{
	mSprite->draw(transform.position, transform.rotationAngle);
}