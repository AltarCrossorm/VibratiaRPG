#include "discordhelpers.hpp"
/**
 * @file discordhelpers.cpp
 * @date 2026/07/13
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include <sstream>
#include "logSystem.hpp"

std::string parseEmoji(unsigned long long snowflake, std::string_view name, bool isAnimated) {
	std::stringstream ss;

	ss << '<' << (isAnimated ? "a" : "") << ':' << name << ':' << std::to_string(snowflake) << '>';
	return ss.str();
}

dpp::task<dpp::confirmation_callback_t> safe_coro(dpp::async<dpp::confirmation_callback_t> task_to_execute) {
    // 1. On exécute et on attend la tâche que tu as passée (ex: l'envoi de message)
    dpp::confirmation_callback_t result = co_await task_to_execute;
	dpp::cluster *bot = const_cast<dpp::cluster*>(result.bot);

    // 2. Comme presque tous les retours de co_await héritent ou contiennent confirmation_callback_t
    // on vérifie s'il y a une erreur de manière générique
    if (result.is_error()) {
        auto err = result.get_error();
        
        // Ton log magique automatique !
        log(err.human_readable, true, logSystem::LSLevel::ERROR, logSystem::LSDirectory::DISCORD);
        
        // Safeguard automatique en cas de Rate Limit
        if (err.code == 429) {
            co_await bot->co_sleep(2000);
        }
    }

    // 3. On te renvoie le résultat original (comme ça tu peux quand même l'analyser si besoin)
    co_return result;
}
