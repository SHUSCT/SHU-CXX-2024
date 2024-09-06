#pragma once

#include <chrono>
#include <numeric>
#include <vector>

#include "shucxx2024/System.hpp"

namespace shucxx2024
{
class SHUCXX2024_API TimeCounter
{
public:
    explicit TimeCounter() = default;
    TimeCounter& operator=(const TimeCounter&) = delete;
    ~TimeCounter() = default;

public:
    // Clear the content in {resultList}.
    void init();

    // Clear the content in {resultList}.
    void reset();

    // Start counting.
    void startCounting();

    // Stop counting and store duration into {resultList}.
    void endCounting();

    // Return average duration in millisecond.
    int64_t msecond();

    // Return average duration in second.
    double second();

private:
    auto calAverage()
        -> std::chrono::high_resolution_clock::duration;

    bool whetherStart = false;
    std::chrono::high_resolution_clock::time_point start;
    std::vector<std::chrono::high_resolution_clock::duration> resultList;
};
}  // namespace shucxx2024