#include <iostream>

#include <03-build-and-link-against-libraries/TimeCounter.hpp>

int main()
{
    shucxx2024::TimeCounter timeCounter;
    timeCounter.startCounting();
    for (int i = 0; i < 10000; ++i) {
        std::cout << i << ",";
    }
    std::cout << std::endl;
    timeCounter.endCounting();
    std::cout << "Average time: " << timeCounter.second() << "s" << std::endl;
    return 0;
}