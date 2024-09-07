#include <iostream>

#include <Yutils/ArgParser.hpp>

#include <shucxx2024/Logger.hpp>
#include <shucxx2024/Math.hpp>
#include <shucxx2024/TimeCounter.hpp>
#include <spdlog/spdlog.h>

int main(int argc, char* argv[])
{
    auto argParser = yutils::ArgParser(argv[0]);
    argParser.addOption("-n", "int", "The number of iterations", "10");
    if (!argParser.parse(argc, argv)) {
        return -1;
    }

    auto logger = shucxx2024::Logger();
    if (argParser.get<yutils::ArgParser::flag_t>("--help")) {
        argParser.getHelpMessage();
        logger.log("\n{}", argParser.getHelpMessage());
        return 0;
    }

    auto nIter = argParser.get<int>("-n");

    shucxx2024::TimeCounter timeCounter;
    timeCounter.startCounting();
    for (int i = 0; i < nIter; ++i) {
        logger.log("The sqrt of {} is {}", i, shucxx2024::sqrt(i));
    }
    timeCounter.endCounting();
    std::cout << "Average time: " << timeCounter.second() << "s" << std::endl;
    return 0;
}