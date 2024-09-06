#pragma once

#if defined(_WIN32) || defined(__WIN32__)
    #if defined(SHUCXX2024_EXPORT)
        #define SHUCXX2024_API __declspec(dllexport)
    #elif defined(SHUCXX2024_IMPORT)
        #define SHUCXX2024_API __declspec(dllimport)
    #else
        #define SHUCXX2024_API
    #endif
#else
    #if defined(SHUCXX2024_EXPORT)
        #define SHUCXX2024_API __attribute__((visibility("default")))
    #else
        #define SHUCXX2024_API
    #endif
#endif