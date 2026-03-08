#pragma once
#include <unordered_map>
#include <vector>
#include <iostream>

#include "Debug.h"

class MemoryTracker
{
public:
	//Static isntance variable
	static MemoryTracker* instance();

	//Add and remove allocations
	void addAllocation(void* alloc, size_t size);
	void removeAllocation(void* alloc);

	void printAllocations();

private:
	//Hide constructor
	MemoryTracker();
	~MemoryTracker();

	//Allocation data
	struct Allocation
	{
		Allocation(int num, size_t size) : num(num), size(size) {};
		int num;
		size_t size;
	};

	//Dont allow copying
	MemoryTracker(const MemoryTracker&);
	MemoryTracker& operator=(const MemoryTracker&);

	//Map of allocations
	std::unordered_map<void*, Allocation> mAllocations;

	static int msAllocationNum;
	static MemoryTracker* mspInstance;
};