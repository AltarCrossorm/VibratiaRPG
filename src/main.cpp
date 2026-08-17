/**
 * @file main.cpp
 * @date 2026/07/07
 * @authors
 *      - CRESP Enguerran
 * @brief Main file... What did you expect lmao ?
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include <dpp/dpp.h>
#include "dotenv.h"
#include <csignal>
#include "sqlite3.hpp"

#include "logSystem.hpp"
#include "config.hpp"
#include "managers/botmanager.hpp"

#include "modules/debugmodule.hpp"
#include "modules/testmodule.hpp"
#include "modules/fightmodule.hpp"

int main() {
    // Load .env file
    dotenv::env.load_dotenv(ROOT_DIRECTORY+"/.env");
    // Init bot context (cluster here)
    dpp::cluster bot(dotenv::env["DISCORD_TOKEN"]);

    // Events filling
    bot.on_log([&bot](const dpp::log_t& event) {
        log(event.message,true,static_cast<logSystem::LSLevel>(event.severity),logSystem::LSDirectory::DISCORD);

        if (event.severity == dpp::ll_critical) {
            log("Arrêt d'urgence provoqué par un log Discord de niveau Critical !",true,logSystem::LSLevel::FATAL, logSystem::LSDirectory::DISCORD);
            
            bot.shutdown(); 
        }
    });
    bot.on_ready([&bot]([[maybe_unused]] const dpp::ready_t& event) {
		log("Bot Lanched",DEBUG_TRUE, logSystem::LSLevel::INFO, logSystem::LSDirectory::DISCORD);
        log("Connecté en tant que " + bot.me.username + "!", true, logSystem::LSLevel::INFO, logSystem::LSDirectory::DISCORD);

    });

	signal(SIGINT,[](int) {
		log("Got signal SIGINT, shutting down.");
		log("Bot was shut down manually", true, logSystem::LSLevel::INFO, logSystem::LSDirectory::DISCORD);
		// Can't easily shutdown the bot... Damn
		exit(0);
	});


    // Managers initialization
    BotManager manager;


	// ---------- Initialization of all modules
    TestModule test;
	FightModule fight;

#ifdef DEBUG_MODE_ENABLED
	DebugModule debug;
	SQLite3::Connection con(ROOT_DIRECTORY+"/databases/testdb.db");
#else
	SQLite3::Connection con(ROOT_DIRECTORY+"/databases/main.db");
#endif
	// ---------- End of Initialization

    // Initialize all managers
    manager.init(bot);

    // Start the bot
    bot.start(dpp::st_wait);
    return 0;
}
