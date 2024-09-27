#pragma once

namespace shucxx2024
{
template <typename F>
struct DeferGuard
{
    F f;
    bool released = false;
    ~DeferGuard()
    {
        if (!released) {
            f();
        }
    }
    void release()
    {
        released = true;
    }
};
}  // namespace shucxx2024