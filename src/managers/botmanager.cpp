#include "managers/botmanager.hpp"

void BotManager::init(dpp::cluster& bot) {

    this->slashCommands->setup(bot);
    this->buttons->setup(bot);
    // this->messages->setup(bot);
    // this->menuSelectors->setup(bot);
    // this->forms->setup(bot);
    // this->guild->setup(bot);
    
    // calls all setups
    // then call every .on_ready method

    bot.on_ready([&bot]([[maybe_unused]] const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_functionnal>()) {
            SlashCommandManager::instance()->on_ready(bot);
            ButtonManager::instance()->on_ready(bot);
            // MessageManager::instance()->on_ready(bot);
            // MenuSelectorManager::instance()->on_ready(bot);
            // FormManager::instance()->on_ready(bot);
            // GuildManager::instance()->on_ready(bot);
        }
    });
}
