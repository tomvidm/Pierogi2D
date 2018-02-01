#ifndef P2D_POOL_HPP
#define P2D_POOL_HPP

#include <deque>

namespace p2d { namespace utility {
    typedef unsigned int uint;

    template <typename T, uint N>
    class Pool {
    public:
        Pool();

        uint getFirstFreeIndex() const; 

        T& operator [] (const uint i);
        T operator[] (const uint i) const;
    private:
        const uint poolSize;

        uint firstUnusedIndex; // 0 - unused, 1 - in use, 2 - used and discarded

        uint storageBitmask[N];
        T storage[N];

        std::deque<uint> freeIndexes;
    }; // Pool

    template <typename T, uint N>
    Pool<T, N>::Pool() 
    : poolSize(N) {
        ;
    } // constructed

    template <typename T, uint N>
    uint Pool<T, N>::getFirstFreeIndex() const {
        if (freeList.front() < firstUnusedIndex) {
            return freeList.front();
        } else {
            return firstUnusedIndex;
        } // if else
    } // getFirstFreeInfex

    template <typename T, uint N>
    T& Pool<T, N>::operator [] (const uint i) {
        return storage[i];
    } // operator []

    template <typename T, uint N>
    T Pool<T, N>::operator [] (const uint i) const {
        return storage[i];
    } // operator []

} // namespace utility
} // namespace p2d



#endif