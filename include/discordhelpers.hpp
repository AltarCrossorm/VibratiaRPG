#pragma once
/**
 * @file discordhelpers.hpp
 * @date 2026/07/13
 * @authors
 *      - 
 * @brief Various helper function for discord management
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include <string>
#include <string_view>
#include <dpp/dpp.h>

#define MESSAGE_HANDLEING [](const dpp::confirmation_callback_t& event) {\
if(event.is_error()) {\
log(event.get_error().human_readable,true,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);\
}\
}

std::string parseEmoji(unsigned long long snowflake, std::string_view name, bool isAnimated);

dpp::task<dpp::confirmation_callback_t> safe_coro(dpp::async<dpp::confirmation_callback_t> task_to_execute);
