#pragma once
#include <string>
#include <map>
#include <vector>
#include <dpp/dpp.h>
#include "dppmanager.hpp"

#define newSlashCommand(func) newDPPObject(slashcommand_t, func)

using SlashCommandCallback = ManagerCallback<dpp::slashcommand_t>;
using SlashOptions = std::vector<dpp::command_option>;

struct SlashCommandGroup;

struct SlashCommandInfo
{
    std::string description;
    SlashOptions options;
    SlashCommandCallback callback;
	std::map<std::string,SlashCommandInfo> subCommands;
	std::map<std::string,SlashCommandGroup> subCommandsGroups;
};

struct SlashCommandGroup
{
	std::string description;
	std::map<std::string,SlashCommandInfo> subCommands;
	SlashOptions options;
};


class SlashCommandManager: public DppManager
{
private:
    static SlashCommandManager* inst;
    std::map<std::string,SlashCommandInfo>* mapCommands = nullptr;
public:
    SlashCommandManager() {
        if(!(this->inst)) this->inst = this;
        this->mapCommands = new std::map<std::string,SlashCommandInfo>;
    }
    ~SlashCommandManager() {
        delete this->mapCommands;
    }
    
    static SlashCommandManager* instance(void);

	static void addSubSlashCommand(
		std::string baseSlashCommandName,
		std::string subSlashCommandName,
		SlashCommandCallback slashCommand,
		std::string description,
		SlashOptions options
	);

	static void addSubGroupSlashCommand(
		std::string baseSlashCommandName,
		std::string subGrpSlashCommandName,
		std::string description
	);

	static void addSubCommandFromGroup(
		std::string baseSlashCommandName,
		std::string subGrpSlashCommandName,
		std::string slashCommandName,
		SlashCommandCallback callback,
		std::string description,
		SlashOptions options
	);
	
    static void addSlashCommand(
        std::string slashCommandName,
        SlashCommandCallback slashCommand,
        std::string description,
        SlashOptions options
    );

    static void addSlashCommand(
        std::string slashCommandName,
        SlashCommandCallback slashCommand,
        std::string description
    );

    static void addSlashCommand(
        std::string slashCommandName,
        SlashCommandCallback slashCommand
    );

    virtual void setup(dpp::cluster& bot) override;
    virtual void on_ready(dpp::cluster& bot) override;

    std::map<std::string,SlashCommandInfo>* getMapCommands(void);
};
