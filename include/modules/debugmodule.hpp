#pragma once
/**
 * @file debugmodule.hpp
 * @date 2026/07/28
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "managers/slashcommandmanager.hpp"
#include <appcommand.h>

class DebugModule
{
public:

	DebugModule() {
		SlashCommandManager::addSlashCommand(
			"debug",
			newSlashCommand(debug),
			"Debug entry point"
		);

		SlashCommandManager::addSubGroupSlashCommand(
			"debug",
			"set",
			"A slash command group setter base"
		);

		SlashCommandManager::addSubGroupSlashCommand(
			"debug",
			"get",
			"A slash command group getter base"
		);


		SlashCommandManager::addSubCommandFromGroup(
			"debug",
			"get",
			"inventory",
			newSlashCommand(getInventory),
			"Obtiens l'inventaire de quelqu'un",
			{
				dpp::command_option(dpp::co_integer,"id","Identifier of the character",true)
			}
		);

		SlashCommandManager::addSubCommandFromGroup(
			"debug",
			"set",
			"character_position",
			newSlashCommand(setCharacterPos),
			"Définis l'emplacement d'un personnage",
			{
				dpp::command_option(dpp::co_integer,"id","Identifiant du personnage",true)
			}
		);

	}

	dpp_async debug(const dpp::slashcommand_t&){co_return;}

	dpp_async getInventory(const dpp::slashcommand_t&);

	dpp_async setCharacterPos(const dpp::slashcommand_t&);
};
