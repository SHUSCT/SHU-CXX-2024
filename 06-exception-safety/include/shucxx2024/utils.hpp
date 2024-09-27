#pragma once
#include "defer_guard.hpp"
#include <memory>

namespace shucxx2024
{
template <typename ForwardIterator, typename T>
void unitialized_fill_v1(ForwardIterator first, ForwardIterator last,
                         const T& value)
{
    auto current{first};
    try {
        for (; current != last; ++current) {
            std::construct_at(std::addressof(*current), value);
        }
    } catch (...) {
        for (auto it{first}; it != current; ++it) {
            std::destroy_at(std::addressof(*it));
        }
        throw;
    }
}
template <typename ForwardIterator, typename T>
void unitialized_fill_v2(ForwardIterator first, ForwardIterator last,
                         const T& value)
{
    auto current{first};
    DeferGuard guard{[&current, first] {
        for (auto it{first}; it != current; ++it) {
            std::destroy_at(std::addressof(*it));
        }
    }};
    for (; current != last; ++current) {
        std::construct_at(std::addressof(*current), value);
    }
    guard.release();
}
}  // namespace shucxx2024