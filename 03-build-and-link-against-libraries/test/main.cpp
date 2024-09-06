#include <iostream>

#include <shucxx2024/Logger.hpp>
#include <shucxx2024/Math.hpp>
#include <shucxx2024/TimeCounter.hpp>

int main()
{
    auto logger = shucxx2024::Logger();
    shucxx2024::TimeCounter timeCounter;
    timeCounter.startCounting();
    for (int i = 0; i < 10; ++i) {
        logger.log("The sqrt of {} is {}", i, shucxx2024::sqrt(i));
    }
    timeCounter.endCounting();
    std::cout << "Average time: " << timeCounter.second() << "s" << std::endl;
    return 0;
}