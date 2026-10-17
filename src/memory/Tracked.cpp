#include "Tracked.h"
#include "MemoryTracker.h"

namespace engine::memory
{
	void* Tracked::operator new(std::size_t size)
	{
		void* ptr = malloc(size);
		MemoryTracker::instance()->addAllocation(ptr, size);
		return ptr;
	}
	void Tracked::operator delete(void* ptr)
	{
		MemoryTracker::instance()->removeAllocation(ptr);
		free(ptr);
	}
	void* Tracked::operator new[](std::size_t size)
	{
		void* ptr = malloc(size);
		MemoryTracker::instance()->addAllocation(ptr, size);
		return ptr;
	}
	void Tracked::operator delete[](void* ptr)
	{
		MemoryTracker::instance()->removeAllocation(ptr);
		free(ptr);
	}
}