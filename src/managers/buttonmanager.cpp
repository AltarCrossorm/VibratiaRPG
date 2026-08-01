#include "managers/buttonmanager.hpp"
/**
 * @file buttonmanager.cpp
 * @date 2026/07/21
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include "logSystem.hpp"
#include "config.hpp"

ButtonManager* ButtonManager::inst = nullptr;

ButtonManager* ButtonManager::instance(void) {
    return inst;
}

void ButtonManager::addButton(std::string&& id, ButtonCallback button, unsigned int timeout) {
    (*ButtonManager::instance()->getMapButtons())[id] = {button, timeout};
}

void ButtonManager::setup(dpp::cluster& bot) {
    bot.on_button_click([](const dpp::button_click_t& event) -> dpp_async {
        std::string custom_id = event.custom_id;
        
        auto it = ButtonManager::instance()->getMapButtons()->find(custom_id);
        if (it != ButtonManager::instance()->getMapButtons()->end()) {
			if (!it->second.timeout || difftime(time(nullptr), event.command.msg.sent) < it->second.timeout) {
				co_await it->second.callback(event);
			} else {
				log("Message was fired despite a timeout by "+event.command.usr.username+" [Difference is "+std::to_string(difftime(event.command.msg.sent,time(nullptr)))+"]", DEBUG_TRUE, logSystem::LSType::ERROR, logSystem::LSDirectory::DISCORD);
			}
        } else {
			log("unknown button id fired : "+event.custom_id, true, logSystem::LSLevel::ERROR, logSystem::LSDirectory::DISCORD);
		}
		co_return;
    });
}

void ButtonManager::on_ready(dpp::cluster&) {
    // Empty function ?
}

std::map<std::string,ButtonInfo>* ButtonManager::getMapButtons(void) {
    return this->mapButtons;
}
