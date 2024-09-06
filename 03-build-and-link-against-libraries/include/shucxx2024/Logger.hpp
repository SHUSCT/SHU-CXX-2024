#pragma once

#include <spdlog/common.h>
#include <spdlog/spdlog.h>
#include <string_view>

#include "shucxx2024/System.hpp"

namespace shucxx2024
{

class SHUCXX2024_API Logger
{
public:
    Logger();
    ~Logger();

    template <typename... Args>
    void log(::spdlog::format_string_t<Args...> fmt, Args&&... args) const
    {
        m_logger->log(spdlog::level::info, fmt, std::forward<Args>(args)...);
    }

private:
    ::std::shared_ptr<spdlog::logger> m_logger;
};

}  // namespace shucxx2024