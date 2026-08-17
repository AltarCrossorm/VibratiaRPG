#include "modules/fightmodule.hpp"
/**
 * @file fightmodule.cpp
 * @date 2026/07/18
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "discordhelpers.hpp"
#include "model/characterpositions.hpp"
#include "model/ennemypool.hpp"
#include "model/fights.hpp"
#include "model/turn.hpp"
#include "sqlite3.hpp"

dpp_async FightModule::fight(const dpp::slashcommand_t& event) {
	co_await safe_coro(event.co_reply("This command should not be invoked."));
}

dpp_async FightModule::start(const dpp::slashcommand_t& event) {
	// dpp::cluster *bot = event.owner;
	long long cur_channel = event.command.channel_id;
	dpp::command_value opp = event.get_parameter("opponent");

	if (opp.index() != 0) {
		co_await safe_coro(event.co_reply("PvP implementation is not available for now."));
		co_return;
	}

		
	
	CharacterPositionsRepository CPRepo;
	if (!CPRepo.isAUserCharacterIsInChannel(cur_channel,event.command.get_issuing_user())) {
		co_await safe_coro(event.co_reply("Aucun personnage à vous n'est dans ce salon."));
		co_return;
	}

	auto chaPos = CPRepo.getPositionsForCharactersOfAUser(event.command.get_issuing_user());
	EnnemiesPoolRepository EPRepo;
	auto ennemyPositionned = EPRepo.getEnnemyFromPosition(cur_channel);
	if (ennemyPositionned) {
		co_await safe_coro(event.co_reply("Cet endroit est bien calme... Pas d'ennemis à l'horizon..."));
		co_return;
	}

	
	FightsRepository FRepo;
	auto remainingFight = FRepo.getLastFightFromPosition(cur_channel);
	if ( remainingFight && !remainingFight.value().isEnded ) {
		co_await safe_coro(event.co_reply("Un combat est déjà en cours, pense à te protéger du danger !"));
		co_return;
	}


	Fights f;
	f.id = std::nullopt;
	f.startFight = time(nullptr);
	f.channelID = cur_channel;
	f.isPvP = false;
	f.opponent1 = chaPos[0].id.value();
	f.opponent2 = ennemyPositionned.value().id.value();
	f.isEnded = false;

	FRepo.add(f);

	CharacterRepository CRepo;
	EnnemyRepository ERepo;

	Character chara = CRepo.findById(chaPos[0].id.value()).value();
	Ennemy en = ERepo.findById(ennemyPositionned.value().id.value()).value();

	dpp::message msg = this->setTurn(f.id.value(),0,FightDistance::FAR,chara,en,false);
	dpp::embed e;
	
	msg.set_channel_id(cur_channel);

	co_await safe_coro(event.co_reply(msg));
}

dpp::message FightModule::setTurn(long fightID, long turn, FightDistance distance, Character character, Ennemy ennemy, bool whoIsFirst) {
	// TODO : Créer un tour


	Turn t;
	t.id = std::nullopt;
	t.fight_id = fightID;
	t.action_timestamp = time(nullptr);
	t.opponent_first = whoIsFirst;
	t.action_first = std::nullopt;
	t.action_second = std::nullopt;
	t.bonus_action = std::nullopt;

	TurnRepository TRepo;
	TRepo.add(t);
	return this->setFightEmbed(fightID,turn,t.id.value(),distance,character.name,ennemy.name);
}

dpp::message FightModule::setTurn(long fightID, long turn, FightDistance distance, Ennemy ennemy, Character character, bool whoIsFirst) {
	// TODO : Créer un tour

	Turn t;
	t.id = std::nullopt;
	t.fight_id = fightID;
	t.action_timestamp = time(nullptr);
	t.opponent_first = whoIsFirst;
	t.action_first = std::nullopt;
	t.action_second = std::nullopt;
	t.bonus_action = std::nullopt;

	TurnRepository TRepo;
	TRepo.add(t);
	return this->setFightEmbed(fightID,turn,t.id.value(),distance,ennemy.name,character.name);
}

dpp::message FightModule::setTurn(long fightID, long turn, FightDistance distance, Character firstCharacter, Character secondCharacter, bool whoIsFirst) {
	// TODO : Créer un tour
	Turn t;
	t.id = std::nullopt;
	t.fight_id = fightID;
	t.action_timestamp = time(nullptr);
	t.opponent_first = whoIsFirst;
	t.action_first = std::nullopt;
	t.action_second = std::nullopt;
	t.bonus_action = std::nullopt;

	TurnRepository TRepo;
	TRepo.add(t);
	return this->setFightEmbed(fightID,turn,t.id.value(),distance,firstCharacter.name,secondCharacter.name);
}

dpp::message FightModule::setFightEmbed(long fightID, long turn, long turnID, FightDistance dist, std::string opponent1Name, std::string opponent2Name) {
	dpp::embed e;
	dpp::embed_footer ef;
	std::string distName;
	dpp::component compo,row;
	dpp::message msg;
	compo
		.set_label("Consulter les options de jeu")
		.set_emoji("📜")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_secondary)
		.set_id("drop_actions");

	row
		.set_type(dpp::cot_action_row)
		.add_component(compo);

	switch(dist){
	case FightDistance::CLOSE:
		distName = "Courte portée";
		break;
	case FightDistance::MIDDLE:
		distName = "Moyenne portée";
		break;
	case FightDistance::FAR:
		distName = "Longue portée";
		break;
	case FightDistance::OUT_OF_REACH:
		[[fallthrough]];
	default:
		distName = "Hors portée";
	}

	ef.set_text("- Fight ID : "+std::to_string(fightID)+" | - Turn ID : "+std::to_string(turnID));

	e.set_title("Combat !")
	 .add_field("Portée",distName,true)
	 .add_field("Tour",std::to_string(turn), true)
	 .add_field("\u200b", "\u200b", false)
	 .add_field("Joue en premier",opponent1Name,true)
	 .add_field("Joue en second",opponent2Name,true)
	 .set_footer(ef);

	msg.add_embed(e)
		.add_component(row);

	return msg;
}


dpp_async FightModule::drop_actions(const dpp::button_click_t& event) {
	dpp::message msg;
	dpp::component row_actions,
					btn_attack, btn_block, btn_dodge, btn_grab, btn_counter,
				   row_special,
					switch_wpn_1, switch_wpn_2, switch_wpn_3, abandon
				   ;
	
	btn_attack
		.set_label("Attaquer")
		.set_emoji("⚔️")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_primary)
		.set_id("attack");

	btn_block
		.set_label("Bloquer")
		.set_emoji("🛡️")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_primary)
		.set_id("block");

	btn_dodge
		.set_label("Esquiver")
		.set_emoji("💨")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_primary)
		.set_id("dodge");

	btn_grab
		.set_label("Atrapper")
		.set_emoji("🫳")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_primary)
		.set_id("grab")
		.set_disabled(true);

	btn_counter
		.set_label("Contrer")
		.set_emoji("🥷")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_primary)
		.set_id("counter");

	
	switch_wpn_1
		.set_label("Changer d'arme vers l'arme 1")
		.set_emoji("🗡️")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_secondary)
		.set_id("change_to_wpn_1");

	switch_wpn_2
		.set_label("Changer d'arme vers l'arme 2")
		.set_emoji("🗡️")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_secondary)
		.set_id("change_to_wpn_2");

	switch_wpn_3
		.set_label("Changer d'arme vers l'arme 3")
		.set_emoji("🗡️")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_secondary)
		.set_id("change_to_wpn_3");

	abandon
		.set_label("Abandonner le combat")
		.set_emoji("🛑")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_danger)
		.set_id("abandon");

	row_actions
		.set_type(dpp::cot_action_row)
		.add_component(btn_attack)
		.add_component(btn_block)
		.add_component(btn_dodge)
		.add_component(btn_grab)
		.add_component(btn_counter);

	row_special
		.set_type(dpp::cot_action_row)
		.add_component(switch_wpn_1)
		.add_component(switch_wpn_2)
		.add_component(switch_wpn_3)
		.add_component(abandon);
	
	msg
		.add_component(row_actions)
		.add_component(row_special)

		.set_flags(dpp::m_ephemeral);

	co_await safe_coro(event.co_reply(msg));
}

dpp_async FightModule::abandon(const dpp::slashcommand_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"fonction activée : __FUNC__"}));
}

dpp_async FightModule::abandon(const dpp::button_click_t& event) {
	
	dpp::message actionsMsg = event.command.msg;
	actionsMsg.set_content("Abandon du combat par "+event.command.get_issuing_user().get_mention());
	actionsMsg.components.clear();

	co_await safe_coro(event.co_reply(/*dpp::ir_deferred_update_message,*/actionsMsg));
}

dpp_async FightModule::info(const dpp::slashcommand_t& event) {
	std::string id = std::to_string(std::get<long int>(event.get_parameter("fight_id")));
	co_await safe_coro(event.co_reply("Activation de la commande **info** with ID "+id));
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"fonction activée : __FUNC__"}));
}

dpp_async FightModule::attack(const dpp::button_click_t& event) {
	co_await safe_coro(event.co_reply("L'action de {} a été prise en compte"));
}

dpp_async FightModule::dodge(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}

dpp_async FightModule::block(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}

dpp_async FightModule::grab(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}

dpp_async FightModule::counter(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}

dpp_async FightModule::changeToWeapon1(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}

dpp_async FightModule::changeToWeapon2(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}

dpp_async FightModule::changeToWeapon3(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
}
