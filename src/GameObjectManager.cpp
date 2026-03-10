#include "GameObjectManager.h"

/*
Initalize the Manger
*/
bool GameObjectManager::init()
{
	Debug::log(DebugColor::CYAN, "[INIT]") << "Game Object Manager Inititialized";
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
	GameObject* newGameObj = new GameObject();
	
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
		Debug::error() << "Game object doesn't exist";
		return false;
	}

	//Destroy
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
		Debug::error() << "Nothing to purge";

	//Delete all objects
	for (GameObject* gObj : mGameObjects)
	{
		delete gObj;
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