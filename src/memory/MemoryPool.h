#pragma once
#include "CircularQueue.h"
#include "Tracked.h"

typedef unsigned char Byte;

class MemoryPool : public Tracked
{
public:
    MemoryPool(uint32_t maxNumObjects, uint32_t objectSize);
    ~MemoryPool() { free(mMemory); delete mpFreeList; };

    void reset();//doesn't reallocate memory but does reset free list and num allocated objects

    Byte* allocateObject();
    void freeObject(Byte* ptr);

    inline uint32_t getMaxObjectSize() const { return mObjectSize; };
    inline uint32_t getNumFreeObjects() const { return mMaxNumObjects - mNumAllocatedObjects; };
    inline uint32_t getMaxNumObjects() const { return mMaxNumObjects; };
    inline uint32_t getTotalMemory() const { return mMaxNumObjects * mObjectSize; };

    bool contains(Byte* ptr) const;

private:
    Byte* mMemory;
    Byte* mHighestValidAddress;
    uint32_t mMaxNumObjects;
    uint32_t mNumAllocatedObjects;
    uint32_t mObjectSize;
    CircularQueue<Byte*>* mpFreeList;

    void createFreeList();
};