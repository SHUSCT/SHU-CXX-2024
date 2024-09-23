#pragma once
#include <memory>
#include <utility>

#include "shucxx2024/helpers.hpp"

namespace shucxx2024
{
template <typename T>
struct DestructOnlyDeleter
{
    void operator()(T* ptr) const noexcept
    {
        std::destroy_at(ptr);
    }
};
template <typename T>
using DestructGuard = std::unique_ptr<T, DestructOnlyDeleter<T>>;

template <typename T, typename A = ::shucxx2024::Allocator<T>>
struct VectorMemory
{
    // fields
    [[no_unique_address]] A alloc;
    T* ptr = nullptr;
    std::size_t cap = 0;

    void swap(VectorMemory& other) noexcept
    {
        std::swap(alloc, other.alloc);
        std::swap(ptr, other.ptr);
        std::swap(cap, other.cap);
    }

    VectorMemory() noexcept = default;
    VectorMemory(std::size_t n) : alloc{}, ptr{alloc.allocate(n)}, cap{n}
    {
    }
    VectorMemory(const VectorMemory&) = delete;
    VectorMemory& operator=(const VectorMemory&) = delete;
    VectorMemory(VectorMemory&& other) noexcept
        : alloc{std::exchange(other.alloc, {})},
          ptr{std::exchange(other.ptr, {})},
          cap{std::exchange(other.cap, 0)}
    {
    }
    VectorMemory& operator=(VectorMemory&& other) noexcept
    {
        this->swap(other);
        return *this;
    }
    ~VectorMemory()
    {
        alloc.deallocate(ptr, cap);
    }

    std::size_t recap_size() const noexcept
    {
        return this->cap == 0 ? 1 : this->cap * 2;
    }
};

template <typename T, typename A = ::shucxx2024::Allocator<T>>
class Vector
{
    // fields
    VectorMemory<T, A> mem;
    std::size_t count{};
    using Mem = VectorMemory<T, A>;

public:
    void swap(Vector& other) noexcept
    {
        mem.swap(other.mem);
        std::swap(count, other.count);
    }

    Vector() noexcept = default;
    Vector(std::size_t n) : mem{n}
    {
        std::uninitialized_fill(mem.ptr, mem.ptr + n, T{});
    }
    Vector(const Vector& other)
    {
        this->mem = Mem(other.count);
        std::uninitialized_copy(other.mem.ptr, other.mem.ptr + other.count,
                                this->mem.ptr);
    }
    Vector& operator=(const Vector& other)
    {
        // 不需要额外考虑自赋值情况
        Vector tmp{other};
        this->swap(tmp);
        return *this;
    }
    Vector(Vector&& other) noexcept
        : mem{std::exchange(other.mem, {})},
          count{std::exchange(other.count, 0)}
    {
    }
    Vector& operator=(Vector&& other) noexcept
    {
        this->swap(other);
        other.mem = {};
        other.count = 0;
        return *this;
    }
    ~Vector()
    {
        std::destroy(mem.ptr, mem.ptr + count);
        // 不需要在Vector析构函数中释放内存，mem析构函数会释放内存
    }

    T& operator[](std::size_t i) noexcept
    {
        return this->mem.ptr[i];
    }
    const T& operator[](std::size_t i) const noexcept
    {
        return this->mem.ptr[i];
    }
    void reserve(
        std::size_t
            n)  // 异常安全，且代码简洁。如果析构函数你也要抛异常那你是啥b。
    {
        if (n < this->mem.cap) {
            return;
        }
        Mem new_mem{n};
        std::uninitialized_move(this->mem.ptr, this->mem.ptr + this->count,
                                new_mem.ptr);
        std::destroy(this->mem.ptr, this->mem.ptr + this->count);
        this->mem = std::move(new_mem);
    }
    template <typename... Args>
    void emplace_back_v1(
        Args&&... args)  // 强异常安全，除非移动抛异常，但是移动不应该抛异常。同理析构函数抛异常你也是啥b。
    {
        if (this->mem.cap > this->count) {  // 不需要扩容
            std::construct_at(this->mem.ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
        } else {  // 需要扩容
            Mem new_mem = Mem(mem.recap_size());
            std::construct_at(new_mem.ptr + this->count,
                              std::forward<Args>(args)...);
            std::uninitialized_move(this->mem.ptr, this->mem.ptr + this->count,
                                    new_mem.ptr);
            std::destroy(this->mem.ptr, this->mem.ptr + this->count);
            this->mem = std::move(new_mem);
            this->count += 1;
        }
    }
    template <typename... Args>
    void emplace_back(
        Args&&... args)  // 强异常安全，同理析构函数抛异常你也是啥b。
    {
        if (this->mem.cap > this->count) {  // 不需要扩容
            std::construct_at(this->mem.ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
        } else {  // 需要扩容
            Mem new_mem = Mem(mem.recap_size());
            std::construct_at(new_mem.ptr + this->count,
                              std::forward<Args>(args)...);
            DestructGuard<T> guard(
                new_mem.ptr + this->count);  // 保证当移动抛异常时，新元素析构
            std::uninitialized_move(this->mem.ptr, this->mem.ptr + this->count,
                                    new_mem.ptr);
            std::destroy(this->mem.ptr, this->mem.ptr + this->count);
            this->mem = std::move(new_mem);
            this->count += 1;
            guard.release();  // 移动成功，释放析构guard
        }
    }
};
}  // namespace shucxx2024