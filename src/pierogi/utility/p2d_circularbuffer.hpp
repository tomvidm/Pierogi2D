#ifndef P2D_CIRCULARBUFFER_HPP
#define P2D_CIRCULARBUFFER_HPP

namespace p2d { namespace utility {
    template <typename T, unsigned int N>
    class CircularBuffer {
    public:
        CircularBuffer();
        T head() const;
        T operator [] (const unsigned int& index) const;
        T& operator [] (const unsigned int& index);

        void push(const T& val);
    private:
        unsigned int headIndex;
        unsigned int size;
        T buffer[N];
    }; // CircularBuffer

    template <typename T, unsigned int N>
    CircularBuffer<T, N>::CircularBuffer() 
    : headIndex(0), size(N) {
        for (unsigned int i = 0; i < size; i++) {
            buffer[i] = T();
        } // for
    } // constructor

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