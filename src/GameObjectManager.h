#pragma once
#include <vector>

#include "Tracked.h"
#include "GameObject.h"
#include "Debug.h"

class GameObject;
class MemoryManager;

class GameObjectManager : public Tracked
{
public:
	//Con/Destructors
	GameObjectManager();
	~GameObjectManager();

	//Manager functions
	bool init(MemoryManager* pMemoryManager);
	void cleanup();

	//Obj creation/deletion
	GameObject* instantiate();
	bool destroy(GameObject* gObj);
	void purge();

private:
	std::vector<GameObject*> mGameObjects;
	MemoryManager* mMemoryManager = nullptr;
};