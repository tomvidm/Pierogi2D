#ifndef P2D_CIRCULARBUFFER_HPP
#define P2D_CIRCULARBUFFER_HPP

namespace p2d { namespace utility {
    template <typename T, unsigned int N>
    class CircularBuffer {
    public:
        T head() const;
        T operator [] (const unsigned int& index) const;
        T& operator [] (const unsigned int& index);

        void push(const T& val);
    private:
        unsigned int headIndex = 0;
        unsigned int size = N;
        T buffer[N];
    }; // CircularBuffer

    template <typename T, unsigned int N>
    T CircularBuffer<T, N>::head() const {
        return buffer[headIndex];
    }

    template <typename T, unsigned int N>
    T CircularBuffer<T, N>::operator [] (const unsigned int& index) const {
        return buffer[(headIndex + index) % size];
    } // operator []

    template <typename T, unsigned int N>
    T& CircularBuffer<T, N>::operator [] (const unsigned int& index) {
        return buffer[(headIndex + index) % size];
    } // operator []

    template <typename T, unsigned int N>
    void CircularBuffer<T, N>::push(const T& val) {
        buffer[headIndex] = val;

        headIndex += 1;
        headIndex %= size;
    } // push
} // namespace utility
} // namespace p2d

#endif