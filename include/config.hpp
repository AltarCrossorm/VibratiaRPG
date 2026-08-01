#pragma once
/**
 * @file config.hpp
 * @date 2026/07/08
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include <string>

constexpr std::string ROOT_DIRECTORY = "..";

#ifdef DEBUG_MODE_ENABLED
constexpr bool DEBUG_TRUE = true;
constexpr unsigned long int GUILD_ID = 1529255831269540032;
#else
constexpr bool DEBUG_TRUE = false;
constexpr unsigned long int GUILD_ID = 1267570316658479145;
#endif

#ifdef PROFILER_MODE_ENABLED
constexpr bool PROFILER_TRUE = true;
#else
constexpr bool PROFILER_TRUE = false;
#endif
