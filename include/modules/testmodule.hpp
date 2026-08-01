#pragma once
/**
 * @file testmodule.hpp
 * @date 2026/07/07
 * @authors
 *      - CRESP Enguerran
 * @brief Module used for dev testing purposes
 *
 * @ai I'm having fun so no AI !!!
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include <dpp/dpp.h>
#include "managers/slashcommandmanager.hpp"

class TestModule
{
private:

public:
    TestModule() {
        SlashCommandManager::addSlashCommand(
            "test",
            newSlashCommand(testMessage),
            "Slash command for testing purposes"
        );
    }

    dpp_async testMessage(const dpp::slashcommand_t& event);
};
