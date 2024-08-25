#pragma once
#include <chrono>
#include <numeric>
#include <vector>

#include "03-build-and-link-against-libraries/System.hpp"
#include "System.hpp"

namespace shucxx2024
{
class TimeCounter
{
public:
    explicit TimeCounter() = default;
    TimeCounter& operator=(const TimeCounter&) = delete;
    ~TimeCounter() = default;

public:
    // Clear the content in {resultList}.
    SHUCXX2024_API void init();

    // Clear the content in {resultList}.
    SHUCXX2024_API void reset();

    // Start counting.
    SHUCXX2024_API void startCounting();

    // Stop counting and store duration into {resultList}.
    SHUCXX2024_API void endCounting();

    // Return average duration in millisecond.
    SHUCXX2024_API int64_t msecond();

    // Return average duration in second.
    SHUCXX2024_API double second();

private:
    SHUCXX2024_API auto calAverage()
        -> std::chrono::high_resolution_clock::duration;

    bool whetherStart = false;
    std::chrono::high_resolution_clock::time_point start;
    std::vector<std::chrono::high_resolution_clock::duration> resultList;
};
}  // namespace shucxx2024