#pragma once
#include <array>
#include <cstddef>

template<typename T, size_t N>
class MemoryPool {
    std::array<T, N>    buffer;
    std::array<bool, N> used{};

public:
    T* allocate() {
        for (size_t i = 0; i < N; i++)
            if (!used[i]) { 
                used[i] = true; 
                return &buffer[i]; 
            }
        return nullptr; // pool full
    }

    void deallocate(T* ptr) {
        size_t i = ptr - buffer.data();
        if (i < N) used[i] = false;
    }
};