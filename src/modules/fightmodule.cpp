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
#include <dispatcher.h>
#include <message.h>

dpp_async FightModule::fight(const dpp::slashcommand_t& event) {
	co_await safe_coro(event.co_reply("This command should not be invoked."));
	co_return;
}

dpp_async FightModule::start(const dpp::slashcommand_t& event) {
	dpp::cluster *bot = event.owner;
	long long cur_channel = event.command.channel_id;

	dpp::message msg;
	dpp::embed e;
	dpp::component compo,row;

	compo
		.set_label("Consulter les options de jeu")
		.set_emoji("📜")
		.set_type(dpp::cot_button)
		.set_style(dpp::cos_secondary)
		.set_id("drop_actions")
	;

	row.set_type(dpp::cot_action_row)
		.add_component(compo);

	e.set_title("Début d'un combat");
	e.add_field("Portée","Longue Portée",true)
	 .add_field("Tour","1", true)
	 //.add_field("\u200b", "\u200b", false)
	 .add_field("Personnage jouant en premier","abc")
	 .add_field("Personnage jouant en second","def");

	msg.set_channel_id(cur_channel)
		.add_embed(e)
		.add_component(row);

	co_await safe_coro(event.co_reply(msg));
	co_return;
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
	co_return;
}

dpp_async FightModule::abandon(const dpp::slashcommand_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"fonction activée : __FUNC__"}));
	co_return;
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
	co_return;
}

dpp_async FightModule::attack(const dpp::button_click_t& event) {
	co_await safe_coro(event.co_reply("L'action de {} a été prise en compte"));
	co_return;
}

dpp_async FightModule::dodge(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}

dpp_async FightModule::block(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}

dpp_async FightModule::grab(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}

dpp_async FightModule::counter(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}

dpp_async FightModule::changeToWeapon1(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}

dpp_async FightModule::changeToWeapon2(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}

dpp_async FightModule::changeToWeapon3(const dpp::button_click_t& event) {
	co_await safe_coro(event.owner->co_message_create({event.command.channel_id,"Bouton activé : __FUNC__"}));
	co_return;
}
