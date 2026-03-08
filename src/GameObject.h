#pragma once
#include "Vector2.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "Tracked.h"

struct Transform : public Tracked
{
	Vector2 position;
	float rotationAngle;
};

class GameObject : public Tracked
{
public:
	Sprite* sprite() { return mSprite; }
	void setSprite(Sprite* sprite) { mSprite = sprite; }

	void update();
	void draw();

	Transform transform;
private:
	friend class GameObjectManager;

	Sprite* mSprite;

	GameObject();
	~GameObject();
};