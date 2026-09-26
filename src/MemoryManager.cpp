#include "MemoryManager.h"

#include "Debug.h"

bool MemoryManager::init(const std::vector<unsigned int>& sizes, const std::vector<unsigned int>& numSlots)
{
    if (sizes.size() == numSlots.size())
    {
        for (unsigned int i = 0; i < sizes.size(); i++)
        {
            // Create a Memory Pool for each object with its size
            mPools.push_back(new MemoryPool(numSlots[i], sizes[i]));
        }
    }
    else
    {
        engine::Debug::error() << "Memory Manager: sizes array length is not equal to slots array size";
        return false;
    }
    return true;
}

void MemoryManager::cleanup()
{
    // Delete all pools and clear it
    for (auto p : mPools)
    {
        delete p;
    }
    mPools.clear();
}

void MemoryManager::reset()
{
}

Byte* MemoryManager::allocate(unsigned int size)
{
    MemoryPool* pool = findBestPool(size);
    if (!pool) return nullptr;

    mAllocatedBytes += size;
    mWastedBytes += pool->getMaxObjectSize() - size;

    // Insert to keep track of size for dealloc
    Byte* byte = pool->allocateObject();
    mSizeMap.insert({ byte, size });

    return byte;
}

void MemoryManager::deallocate(Byte* ptr)
{
    MemoryPool* pool = findPoolWithData(ptr);

    // Check we found a pool
    if (pool == nullptr)
    {
        std::cout << "Pool not found\n";
        return;
    }

    // Check we have the size
    auto it = mSizeMap.find(ptr);
    if (it == mSizeMap.end())
    {
        std::cout << "Byte not in size map\n";
        return;
    }

    mAllocatedBytes -= it->second; // Remove size
    mWastedBytes -= pool->getMaxObjectSize() - it->second;
    pool->freeObject(ptr);
}

unsigned int MemoryManager::getTotalAllocated() const
{
    return mAllocatedBytes;
}

unsigned int MemoryManager::getTotalCapacity() const
{
    unsigned int total = 0;
    for (auto p : mPools)
    {
        total += p->getTotalMemory();
    }
    return total;
}

unsigned int MemoryManager::getTotalWaste() const
{
    return mWastedBytes;
}

MemoryPool* MemoryManager::findBestPool(unsigned int size)
{
    MemoryPool* closestPool = nullptr;
    for (auto p : mPools)
    {
        // Keep going if pool is too small
        if (p->getMaxObjectSize() < size)
        {
            continue;
        }

        // If the object will fit try the difference to make sure its the most efficient
        if (p->getMaxObjectSize() >= size)
        {
            // continue of the pool is full
            if (p->getNumFreeObjects() <= 0) continue;

            if (!closestPool)
                closestPool = p;
            else if (p->getMaxObjectSize() - size < closestPool->getMaxObjectSize() - size)
                closestPool = p;
        }
    }
    if (!closestPool) std::cout << "ERR// Could not find available pool for sizeof: " << size << "\n";

    return closestPool;
}
MemoryPool* MemoryManager::findPoolWithData(Byte* ptr)
{
    for (auto p : mPools)
    {
        if (p->contains(ptr))
            return p;
    }
    std::cout << "ERR// No pool found that contains: " << ptr << "\n";
    return nullptr;
}