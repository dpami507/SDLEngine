#pragma once
#include <vector>

#include "Tracked.h"
#include "GameObject.h"
#include "Debug.h"

class GameObject;

namespace engine::memory { class MemoryManager; };

class GameObjectManager : public engine::memory::Tracked
{
public:
	//Con/Destructors
	GameObjectManager();
	~GameObjectManager();

	//Manager functions
	bool init(engine::memory::MemoryManager* pMemoryManager);
	void cleanup();

	//Obj creation/deletion
	GameObject* instantiate();
	bool destroy(GameObject* gObj);
	void purge();

private:
	std::vector<GameObject*> mGameObjects;
	engine::memory::MemoryManager* mMemoryManager = nullptr;
};