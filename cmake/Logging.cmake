string(ASCII 27 Esc)

set(SHUCXX2024_LOG_RED "${Esc}[0;31m")
set(SHUCXX2024_LOG_GREEN "${Esc}[0;32m")
set(SHUCXX2024_LOG_YELLOW "${Esc}[0;33m")
set(SHUCXX2024_LOG_BLUE "${Esc}[0;34m")
set(SHUCXX2024_LOG_PURPLE "${Esc}[0;35m")
set(SHUCXX2024_LOG_CYAN "${Esc}[0;36m")
set(SHUCXX2024_LOG_WHITE "${Esc}[0;37m")
set(SHUCXX2024_LOG_RESET "${Esc}[m")

set(SHUCXX2024_LOG_CAT "${SHUCXX2024_LOG_PURPLE}ᓚᘏᗢ${SHUCXX2024_LOG_RESET}")

set(SHUCXX2024_LOG_PREFIX "SHU-CXX-2024")

function(shucxx2024_log_info msg)
    message(STATUS "[${SHUCXX2024_LOG_PREFIX}|${SHUCXX2024_LOG_GREEN}INFO${SHUCXX2024_LOG_RESET}] >>> ${msg}")
endfunction(shucxx2024_log_info msg)

function(shucxx2024_log_warning msg)
    message(WARNING "[${SHUCXX2024_LOG_PREFIX}|WARNING] >>> ${msg}")
endfunction(shucxx2024_log_warning msg)

function(shucxx2024_log_error msg)
    message(SEND_ERROR "[${SHUCXX2024_LOG_PREFIX}|ERROR] >>> ${msg}")
endfunction(shucxx2024_log_error msg)

function(shucxx2024_log_fatal msg)
    message(FATAL_ERROR "[${SHUCXX2024_LOG_PREFIX}|FATAL] >>> ${msg}")
endfunction(shucxx2024_log_fatal msg)