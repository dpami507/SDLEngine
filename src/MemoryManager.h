#pragma once

#include "Tracked.h"
#include "MemoryPool.h"

#include <vector>
#include <unordered_map>

#include <new>

class MemoryManager :public Tracked
{
public:
    MemoryManager() {};
    ~MemoryManager() { cleanup(); };

    void init(const std::vector<unsigned int>& sizes,
        const std::vector<unsigned int>& numSlots);
    void cleanup();
    void reset();
    Byte* allocate(unsigned int size);
    void deallocate(Byte* ptr);
    unsigned int getTotalAllocated() const;//how much memory has been allocated (includes waste)
    unsigned int getTotalCapacity() const;//total amount of theoretically available memory
    unsigned int getTotalWaste() const;

private:
    std::vector<MemoryPool*> mPools;
    unsigned int mWastedBytes = 0;
    unsigned int mAllocatedBytes = 0;
    std::unordered_map<Byte*, int> mSizeMap;

    MemoryPool* findBestPool(unsigned int size);
    MemoryPool* findPoolWithData(Byte* ptr);
};
