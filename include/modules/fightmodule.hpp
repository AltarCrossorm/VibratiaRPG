#pragma once
/**
 * @file fightmodule.hpp
 * @date 2026/07/18
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include "managers/slashcommandmanager.hpp"
#include "managers/buttonmanager.hpp"
#include "model/character.hpp"
#include "model/ennemy.hpp"

enum class FightDistance
{
	CLOSE,
	MIDDLE,
	FAR,
	OUT_OF_REACH,
};

class FightModule
{
	dpp::message setFightEmbed(long fightID, long turn, long turnID, FightDistance dist, std::string opponent1Name, std::string opponent2Name);
public:

	FightModule()
	{
		SlashCommandManager::addSlashCommand(
            "fight",
            newSlashCommand(fight),
            "Base command for the fight system"
        );

		SlashCommandManager::addSubSlashCommand(
			"fight",
			"start",
			newSlashCommand(start),
			"Commencer un combat",
			{
				dpp::command_option(dpp::co_string,"opponent","Choose an opponent", false)
					.add_localization("fr","adversaire","Sélectionnez un adversaire à affronter")
			}
		);

		SlashCommandManager::addSubSlashCommand(
			"fight",
			"info",
			newSlashCommand(info),
			"Get information about a fight",
			{
				{dpp::co_integer,"identifiant","l'Identifiant du combat", true}
			}
		);

		SlashCommandManager::addSubSlashCommand(
			"fight",
			"abandon",
			newSlashCommand(abandon),
			"Get information about a fight",
			{
				{dpp::co_string,"personnage","Le personnager qui abandonne le combat", true}
			}
		);

		ButtonManager::addButton(
			"drop_actions",
			newButton(drop_actions)
		);

		ButtonManager::addButton(
			"attack",
			newButton(attack)
		);

		ButtonManager::addButton(
			"dodge",
			newButton(dodge)
		);

		ButtonManager::addButton(
			"block",
			newButton(block)
		);

		ButtonManager::addButton(
			"grab",
			newButton(grab)
		);

		ButtonManager::addButton(
			"counter",
			newButton(counter)
		);
		
		ButtonManager::addButton(
			"change_to_wpn_1",
			newButton(changeToWeapon1)
		);
		
		ButtonManager::addButton(
			"change_to_wpn_2",
			newButton(changeToWeapon2)
		);
		
		ButtonManager::addButton(
			"change_to_wpn_3",
			newButton(changeToWeapon3)
		);
		
		ButtonManager::addButton(
			"abandon", 
			newButton(abandon)
		);	
	}

	dpp_async fight(const dpp::slashcommand_t&); // base of class commands

	dpp_async start(const dpp::slashcommand_t&);
	dpp_async abandon(const dpp::slashcommand_t&);
	dpp_async info(const dpp::slashcommand_t&);

	dpp_async drop_actions(const dpp::button_click_t&);
	dpp_async attack(const dpp::button_click_t&);
	dpp_async dodge(const dpp::button_click_t&);
	dpp_async block(const dpp::button_click_t&);
	dpp_async grab(const dpp::button_click_t&);
	dpp_async counter(const dpp::button_click_t&);
	dpp_async abandon(const dpp::button_click_t&);
	
	dpp_async changeToWeapon1(const dpp::button_click_t&);
	dpp_async changeToWeapon2(const dpp::button_click_t&);
	dpp_async changeToWeapon3(const dpp::button_click_t&);

	dpp::message setTurn(long fightID, long turn, FightDistance distance, Character character, Ennemy ennemy, bool whoIsFirst);
	dpp::message setTurn(long fightID, long turn, FightDistance distance, Ennemy ennemy, Character character, bool whoIsFirst);
	dpp::message setTurn(long fightID, long turn, FightDistance distance, Character firstCharacter, Character secondCharacter, bool whoIsFirst);
};
