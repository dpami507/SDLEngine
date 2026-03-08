#include "MemoryTracker.h"

int MemoryTracker::msAllocationNum = 0;
MemoryTracker* MemoryTracker::mspInstance = nullptr;

//Get instance
MemoryTracker* MemoryTracker::instance()
{
	//Create Memory tracker if it hasn't been bade already
	if (mspInstance == nullptr)
		mspInstance = new MemoryTracker;

	//Return instance
	return mspInstance;
}

/*
Add memory allocation
@param ptr: memory address to add
@param size: size of memory
*/
void MemoryTracker::addAllocation(void* ptr, size_t size)
{
	if (mAllocations.find(ptr) != mAllocations.end())
	{
		//Already Exists
	}
	else
	{
		//Add to allocations
		Allocation newRec(msAllocationNum, size);
		mAllocations.insert({ ptr, newRec });
		msAllocationNum++;
	}
}
/*
Remove memory allocation
@param memory address to remove
*/
void MemoryTracker::removeAllocation(void* ptr)
{
	if (mAllocations.find(ptr) == mAllocations.end())
	{
		//Doesnt Exist
	}
	else
	{
		//Remove from list
		mAllocations.erase(mAllocations.find(ptr));
	}
}
//Print out all allocations
void MemoryTracker::printAllocations()
{
	size_t totalBytes = 0;

	//Print header
	std::cout << "\nMemory Allocations: " << mAllocations.size() << "\n";

	//Create a line
	std::cout << std::string(25, '-') << "\n";

	//Go through all and print allocations
	for (const auto& a : mAllocations)
	{
		Debug::warning() << "Allocation #" << a.second.num << ", found at: " << a.first << " size: " << a.second.size;
		totalBytes += a.second.size;
	}

	//Create a line
	std::cout << std::string(25, '-') << "\n";

	std::cout << "Total size of " << totalBytes << " bytes\n";
}

MemoryTracker::MemoryTracker()
{
}

MemoryTracker::~MemoryTracker()
{

}