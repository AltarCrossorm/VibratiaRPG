#pragma once
/**
 * @file movementmodule.hpp
 * @date 2026/08/03
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "managers/slashcommandmanager.hpp"

class MovementModule
{
public:
	MovementModule() {
		SlashCommandManager::addSlashCommand(
			"move",
			newSlashCommand(move)
		);
		SlashCommandManager::addSubSlashCommand(
			"move",
			"character",
			newSlashCommand(character),
			"Déplacer ton personnage",
			{
				dpp::command_option(dpp::co_channel,"choix","Choisis où aller !", true)
					.set_auto_complete(true),
				dpp::command_option(dpp::co_string,"personnage","Désigne le personnage qui s'en va de cet endroit", true)
					.set_auto_complete(true)
			}
		);
	}

	dpp_async move(const dpp::slashcommand_t&){};
	dpp_async character(const dpp::slashcommand_t&);
};
