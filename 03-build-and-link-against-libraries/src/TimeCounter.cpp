#include "shucxx2024/TimeCounter.hpp"

namespace shucxx2024
{

void TimeCounter::init()
{
    resultList.clear();
    whetherStart = false;
}

void TimeCounter::reset()
{
    resultList.clear();
    whetherStart = false;
}
void TimeCounter::startCounting()
{
    start = std::chrono::high_resolution_clock::now();
    whetherStart = true;
}

void TimeCounter::endCounting()
{
    if (!whetherStart) {
        throw std::runtime_error("End Counting before starting.");
    }
    auto end = std::chrono::high_resolution_clock::now();
    resultList.push_back(end - start);
    whetherStart = false;
}

int64_t TimeCounter::msecond()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(calAverage())
        .count();
}

double TimeCounter::second()
{
    return std::chrono::duration_cast<std::chrono::duration<double>>(
               calAverage())
        .count();
}

auto TimeCounter::calAverage() -> std::chrono::high_resolution_clock::duration
{
    auto sum =
        std::accumulate(resultList.begin(), resultList.end(),
                        std::chrono::high_resolution_clock::duration::zero());
    return sum / resultList.size();
}

}  // namespace shucxx2024