#include "GameObjectManager.h"
#include "MemoryManager.h"

/*
Initalize the Manger
*/
bool GameObjectManager::init(MemoryManager* pMemoryManager)
{
	mMemoryManager = pMemoryManager;

	engine::Debug::log(engine::DBG_BLUE, "[INIT]") << "Game Object Manager Inititialized";
	return true;
}
/*
Destroys the Manger
*/
void GameObjectManager::cleanup()
{
	//Purge the vector
	purge();
}

/*
Create a GameObject*
@return Created GameObject*
*/
GameObject* GameObjectManager::instantiate()
{
	//Creating new obj
	Byte* allocByte = mMemoryManager->allocate(sizeof(GameObject));
	if (allocByte == nullptr) return nullptr;

	GameObject* newGameObj = new (allocByte) GameObject();
	
	//Add to vector
	mGameObjects.push_back(newGameObj);

	//return
	return newGameObj;
}
/*
Destroys Gameobject
@param GameObject to be destroyed
@return returns true if successfully destroyed
*/
bool GameObjectManager::destroy(GameObject* gObj)
{
	//Find it and make sure it exists
	auto it = std::find(mGameObjects.begin(), mGameObjects.end(), gObj);
	if (it == mGameObjects.end())
	{
		engine::Debug::error() << "Game object doesn't exist";
		return false;
	}

	//Destroy
	mMemoryManager->deallocate((Byte*)gObj);
	mGameObjects.erase(it);
	return true;
}
/*
Destroys All Gameobject
*/
void GameObjectManager::purge()
{
	//Make sure there are things to delete
	if (mGameObjects.size() <= 0)
		engine::Debug::error() << "Game Object Manager: Nothing to purge";

	//Delete all objects
	for (GameObject* gObj : mGameObjects)
	{
		mMemoryManager->deallocate((Byte*)gObj);
		//delete gObj;
	}
	//Clear the list
	mGameObjects.clear();
}

GameObjectManager::GameObjectManager()
{
}
GameObjectManager::~GameObjectManager()
{
	cleanup();
}