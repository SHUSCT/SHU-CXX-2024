#pragma once
#include <cstddef>
#include <deque>
#include <memory>
#include <new>

#include "shucxx2024/helpers.hpp"

namespace shucxx2024
{
template <typename T, typename A = ::shucxx2024::Allocator<T>>
class Vector
{
    [[no_unique_address]] A alloc;
    T* ptr = nullptr;
    std::size_t count = 0;
    std::size_t cap = 0;

private:
    std::size_t recap_size() const noexcept
    {
        return this->cap == 0 ? 1 : this->cap * 2;
    }

public:
    ~Vector()
    {
        std::destroy(this->ptr, this->ptr + this->count);
        alloc.deallocate(ptr, cap);
    }
    Vector() noexcept = default;
    Vector(std::size_t n) : alloc{}, ptr{alloc.allocate(n)}, count{n}, cap{n}
    {
        std::uninitialized_fill(ptr, ptr + n, T{});
    }
    Vector(const Vector& other)
        : alloc{},
          ptr{alloc.allocate(other.count)},
          count{other.count},
          cap{other.count}
    {
        std::uninitialized_copy(ptr, ptr + other.count, other.ptr);
    }
    Vector(Vector&& other) noexcept
        : alloc{std::exchange(other.alloc, {})},
          ptr{std::exchange(other.ptr, {})},
          count{std::exchange(other.count, 0)},
          cap{std::exchange(other.cap, 0)}
    {
    }
    Vector& operator=(const Vector& other)
    {
        if (this == &other) {
            return *this;
        }
        std::destroy_at(this);
        std::construct_at(this, other);
        return *this;
    }
    Vector& operator=(Vector&& other) noexcept
    {
        if (this == &other) {
            return *this;
        }
        std::destroy_at(this);
        std::construct_at(this, std::move(other));
        return *this;
    }
    void reserve(size_t n)  // 非异常安全，仅供演示
    {
        if (n < this->cap) {
            return;
        }
        T* new_ptr = alloc.allocate(n);
        std::uninitialized_move(this->ptr, this->ptr + this->count, new_ptr);
        std::destroy(this->ptr, this->ptr + this->count);
        alloc.deallocate(this->ptr, this->cap);
        this->ptr = new_ptr;
    }
    T& operator[](std::size_t i) noexcept
    {
        return this->ptr[i];
    }
    const T& operator[](std::size_t i) const noexcept
    {
        return this->ptr[i];
    }
    template <typename... Args>
    void emplace_back_v1(
        Args&&... args)  // 非异常安全，如果新元素构造失败，扩容的内存会泄漏
    {
        if (this->cap > this->count) {  // 不需要扩容
            std::construct_at(this->ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
        } else {  // 需要扩容
            T* new_ptr = alloc.allocate(recap_size());
            std::construct_at(new_ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
            std::uninitialized_move(this->ptr, this->ptr + this->count,
                                    new_ptr);
            std::destroy(this->ptr, this->ptr + this->count);
            alloc.deallocate(this->ptr, this->cap);
            this->ptr = new_ptr;
            this->cap = recap_size();
        }
    }
    template <typename... Args>
    void emplace_back_v2(
        Args&&... args)  // 只做到基本异常保证，不能保证构造新对象失败时，原迭代器不失效
    {
        if (this->cap > this->count) {  // 不需要扩容
            std::construct_at(this->ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
        } else {  // 需要扩容
            this->reserve(recap_size(this->cap));
            std::construct_at(this->ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
        }
    }

    template <typename... Args>
    void emplace_back(
        Args... args)  // 异常安全，但是效率不高。而且需要嵌套的层数太多，不易维护。要不是使用了std::uninitialized_move，还需要处理原内存的析构。
    {
        if (this->cap > this->count) {  // 不需要扩容
            std::construct_at(this->ptr + this->count,
                              std::forward<Args>(args)...);
            this->count += 1;
        } else {  // 需要扩容
            try {
                T* new_ptr = alloc.allocate(recap_size());
                try {
                    std::construct_at(new_ptr + this->count,
                                      std::forward<Args>(args)...);
                } catch (...) {  // 构造失败
                    alloc.deallocate(new_ptr, recap_size());
                    throw;
                }
                try {
                    std::uninitialized_move(this->ptr, this->ptr + this->count,
                                            new_ptr);
                } catch (...) {
                    std::destroy_at(new_ptr + this->count);
                    alloc.deallocate(new_ptr, recap_size());
                    throw;
                }
                std::destroy(this->ptr, this->ptr + this->count);
                alloc.deallocate(
                    this->ptr, this->cap);  // Oh! Thankfully it's noexcept!
                                            // Otherwise, we need to handle it.
                this->ptr = new_ptr;
                this->cap = recap_size();
                this->count += 1;
            } catch (...) {
                throw;
            }
        }
    }
};
}  // namespace shucxx2024