#include <spdlog/sinks/stdout_color_sinks.h>

#include "shucxx2024/Logger.hpp"

namespace shucxx2024
{
Logger::Logger()
{
    m_logger = spdlog::stdout_color_mt("shucxx2024");
}

Logger::~Logger()
{
    spdlog::drop("shucxx2024");
}

}  // namespace shucxx2024