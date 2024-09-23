#pragma once
#include <cstddef>
#include <cstdint>
#include <format>
#include <iostream>
#include <utility>

namespace shucxx2024
{
template <typename T>
struct Allocator
{
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using propagate_on_container_move_assignment = std::true_type;

    Allocator() noexcept = default;
    Allocator(const Allocator&) noexcept = default;
    ~Allocator() noexcept = default;
    Allocator& operator=(const Allocator&) noexcept = default;
    [[nodiscard("Allocation pointer discarded results in memory leak.")]] T*
    allocate(size_type n)
    {
        std::cout << std::format("Allocating {} bytes.\n", n * sizeof(T));
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }
    void deallocate(T* p, size_type n) noexcept
    {
        std::cout << std::format("Deallocating {} bytes at {:#x}.\n",
                                 n * sizeof(T), reinterpret_cast<uintptr_t>(p));
        ::operator delete(p, n * sizeof(T));
    }
};
}  // namespace shucxx2024