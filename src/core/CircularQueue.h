#pragma once
#include "Tracked.h"

template < class T >
class CircularQueue : public Tracked
{
public:
    explicit CircularQueue(uint32_t size)
        : mCapacity(size)
        , mFront(0)
        , mBack(0)
        , mNumEntries(0)
    {
        mArray = new T[size];
    }

    ~CircularQueue()
    {
        delete[] mArray;
    }

    void reset()
    {
        mFront = 0;
        mBack = 0;
        mNumEntries = 0;
    }

    bool pushBack(const T& item)//return false if not successfully added (not enough space)
    {
        if (mNumEntries >= mCapacity)//no room left
            return false;

        mArray[mBack] = item;
        mBack++;
        mNumEntries++;

        if (mBack >= mCapacity)
        {
            mBack = 0;
        }

        return true;
    }

    bool popFront(T& item)//returns false if queue is empty
    {
        if (mNumEntries == 0)//empty
            return false;

        item = mArray[mFront];
        mFront++;
        mNumEntries--;

        if (mFront >= mCapacity)
        {
            mFront = 0;
        }

        return true;
    }
private:
    T* mArray;
    uint32_t mCapacity;
    uint32_t mBack;
    uint32_t mFront;
    uint32_t mNumEntries;
};
