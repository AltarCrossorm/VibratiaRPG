#include "managers/slashcommandmanager.hpp"
/**
 * @file slashcommandmanager.cpp
 * @date 2026/07/22
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include <appcommand.h>
#include <ranges>
#include "logSystem.hpp"
#include "config.hpp"


std::string getOptionName(dpp::command_option_type ot) {
	switch(ot) {
	case dpp::command_option_type::co_sub_command:
		return "co_sub_command";
	case dpp::command_option_type::co_sub_command_group:
		return "co_sub_command_group";
	case dpp::command_option_type::co_string:
		return "co_string";
	case dpp::command_option_type::co_integer:
		return "co_integer";
	case dpp::command_option_type::co_boolean:
		return "co_boolean";
	case dpp::command_option_type::co_user:
		return "co_user";
	case dpp::command_option_type::co_channel:
		return "co_channel";
	case dpp::command_option_type::co_role:
		return "co_role";
	case dpp::command_option_type::co_mentionable:
		return "co_mentionnable";
	case dpp::command_option_type::co_number:
		return "co_number";
	case dpp::command_option_type::co_attachment:
		return "co_attachment";
	default:
		return "unknown";
	}
}

SlashCommandManager* SlashCommandManager::inst = nullptr;

SlashCommandManager* SlashCommandManager::instance(void) {
	return inst;
}

std::map<std::string,SlashCommandInfo>* SlashCommandManager::getMapCommands(void) {
	return this->mapCommands;
}

void SlashCommandManager::addSubSlashCommand(
	std::string baseSlashCommandName,
	std::string subSlashCommandName,
	SlashCommandCallback slashCommand,
	std::string description,
	SlashOptions options
	) {
	(*SlashCommandManager::instance()->getMapCommands())[baseSlashCommandName].subCommands[subSlashCommandName] = {description, options, slashCommand, {}, {}};
	(*SlashCommandManager::instance()->getMapCommands())[baseSlashCommandName].options.push_back(dpp::command_option(dpp::co_sub_command,subSlashCommandName,description));
}

void addSubGroupSlashCommand(
		std::string baseSlashCommandName,
		std::string subGrpSlashCommandName,
		std::string description
	) {
	(*SlashCommandManager::instance()->getMapCommands())[baseSlashCommandName].subCommandsGroups[subGrpSlashCommandName] = {description, {}, {}};
	(*SlashCommandManager::instance()->getMapCommands())[baseSlashCommandName].options.push_back(dpp::command_option(dpp::co_sub_command_group,subGrpSlashCommandName,description));
}

void SlashCommandManager::addSlashCommand(
	std::string slashCommandName,
	SlashCommandCallback slashCommand,
	std::string description,
	SlashOptions options
	) {
	(*SlashCommandManager::instance()->getMapCommands())[slashCommandName] = {description, options, slashCommand, {}, {}};
}

void SlashCommandManager::addSlashCommand(
	std::string slashCommandName,
	SlashCommandCallback slashCommand,
	std::string description
	) {
	(*SlashCommandManager::instance()->getMapCommands())[slashCommandName] = {description, {}, slashCommand, {}, {}};
}

void SlashCommandManager::addSlashCommand(
	std::string slashCommandName,
	SlashCommandCallback slashCommand
	) {
	(*SlashCommandManager::instance()->getMapCommands())[slashCommandName] = {"", {}, slashCommand, {}, {}};
}

void SlashCommandManager::setup(dpp::cluster& bot) {

	bot.on_slashcommand([](const dpp::slashcommand_t event) -> dpp_async {
		std::string name = event.command.get_command_name();
		std::string fullEventName = name;
		auto it = (*SlashCommandManager::instance()->getMapCommands()).find(name);
		if (it != (*SlashCommandManager::instance()->getMapCommands()).end()) {
			// Checks if a subcommand or subcommand group exists
			if(!(event.command.get_command_interaction().options.empty()) &&(
				 	event.command.get_command_interaction().options[0].type == dpp::command_option_type::co_sub_command ||
					event.command.get_command_interaction().options[0].type == dpp::command_option_type::co_sub_command_group)) {
				dpp::command_data_option opt = event.command.get_command_interaction().options[0];
				fullEventName += " " + opt.name;
				log("Subcommand: "+fullEventName + " with name: "+opt.name+" and type "+getOptionName(opt.type),true,logSystem::LSLevel::INFO,logSystem::LSDirectory::DISCORD);

				if (opt.type == dpp::command_option_type::co_sub_command) {
					log("SubCommand indeed!",DEBUG_TRUE,logSystem::LSLevel::INFO,logSystem::LSDirectory::DISCORD);
					auto it2 = it->second.subCommands.find(opt.name);

					if (it2 != it->second.subCommands.end()) {
						log("SubCommand found!",DEBUG_TRUE,logSystem::LSLevel::INFO,logSystem::LSDirectory::DISCORD);
						co_await it2->second.callback(event);
						co_return;
					}	
					else {
						log("Unknown subcommand fired: "+fullEventName,true,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);
						co_return;
					}
				}

				if (opt.type == dpp::command_option_type::co_sub_command_group) {
					auto it2 = it->second.subCommandsGroups.find(opt.name);
					auto sub_opt = opt.options[0];

					auto it3 = it2->second.subCommands.find(sub_opt.name);
					auto final_opt = sub_opt.options[0];
					fullEventName += " " + sub_opt.name + " " + final_opt.name;

					if (it3 != it2->second.subCommands.end()) {
						co_await it3->second.callback(event);
						co_return;
					} else {
						log("Unknown subcommand from group fired: "+fullEventName,DEBUG_TRUE,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);
						co_return;
					}
				}

				log("Unknown command fired: "+fullEventName,DEBUG_TRUE,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);
				co_return;
				
			} else {
				co_await it->second.callback(event);
			}
		} else {
			log("Unknown command fired: "+fullEventName,DEBUG_TRUE,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);
		}
		co_return;
	});
}

void SlashCommandManager::on_ready(dpp::cluster& bot) {
	std::vector<dpp::slashcommand> dpp_commands;
			
	for (const auto& [name, info] : (*SlashCommandManager::instance()->getMapCommands())) {
		dpp::slashcommand cmd(name, info.description, bot.me.id);

		for (const auto& opt : info.options) {
			cmd.add_option(opt);
		}

		if (!(info.subCommands.empty())) {
			for(const auto& [nameSub,infoSub] : info.subCommands) {
				for (auto& optSub : cmd.options) {
					if (optSub.name == nameSub && optSub.type == dpp::command_option_type::co_sub_command) {
						for (auto& opts : infoSub.options) {
							optSub.add_option(opts);
						}
					}
				}
			}
		}

		if (!((*SlashCommandManager::instance()->getMapCommands())[name].subCommandsGroups.empty())) {
			for (const auto& [nameGrp, infoGrp] : info.subCommandsGroups) {
				for (auto& optGrp : cmd.options) {
					if (optGrp.name == nameGrp && optGrp.type == dpp::command_option_type::co_sub_command_group) {
						for (auto commds : infoGrp.options) {
							for (const auto& [nameSub, subcmd] : infoGrp.subCommands) {
								for (auto& finalopts : subcmd.options) {
									commds.add_option(finalopts);
								}
							}
							optGrp.add_option(commds);
						}
					}
				}
			}
		}

		dpp_commands.push_back(cmd);
	}
	bot.guild_bulk_command_create(dpp_commands,GUILD_ID);
}
