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
			"Debug entry point",
			{}
		);

		SlashCommandManager::addSubSlashCommand(
			"debug",
			"get_inventory",
			newSlashCommand(getInventory),
			"get the inventory of a user",
			{
				{
					dpp::co_integer,
					"id",
					"Identifier of the character",
					true
				}
			}
		);
	}

	dpp_async debug(const dpp::slashcommand_t&){co_return;}

	dpp_async getInventory(const dpp::slashcommand_t&);
};
