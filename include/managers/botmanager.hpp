#pragma once
#include "slashcommandmanager.hpp"
#include "buttonmanager.hpp"
#include "messagemanager.hpp"

class BotManager {
    SlashCommandManager* slashCommands;
    ButtonManager* buttons;
    MessageManager* messages;
    // MenuSelectorManager* menuSelectors;
    // FormManager* forms
    // GuildManager* guild;
	// PollManager* polls;
	// ReactionManager* reactions;
	// InviteManager* invites;
	// ChannelManager* channels; // May be not interesting to use
	// ThreadManager* threads;
	// ContextMenuManager* contextmenus;

public:
    BotManager(void)
    :
    slashCommands(new SlashCommandManager)
    ,buttons(new ButtonManager)
    ,messages(new MessageManager)
    // ,menuSelectors(new MenuSelectorManager)
    // ,forms(new FormManager)
    // ,guild(new GuildManager)
    {}

    void init(dpp::cluster& bot);
};
