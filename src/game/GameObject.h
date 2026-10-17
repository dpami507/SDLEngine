#pragma once
#include "Vector2.h"
#include "Sprite.h"
#include "GameObjectManager.h"
#include "Tracked.h"

struct Transform : public engine::memory::Tracked
{
	engine::math::Vector2 position;
	float rotationAngle;
};

class GameObject : public engine::memory::Tracked
{
public:
	engine::graphics::Sprite* sprite() { return mSprite; }
	void setSprite(engine::graphics::Sprite* sprite) { mSprite = sprite; }

	void update();
	void draw();

	Transform transform;
private:
	friend class GameObjectManager;

	engine::graphics::Sprite* mSprite;

	GameObject();
	~GameObject() = default;
};