#include "modules/testmodule.hpp"
/**
 * @file testmodule.cpp
 * @date 2026/07/07
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "config.hpp"
#include <string>
#include <sstream>
#include <nlohmann/json.hpp>
#include "discordhelpers.hpp"
#include "logSystem.hpp"
#include "model/enums/weapontype.hpp"
#include "sqlite3.hpp"
#include "ansi.hpp"
#include "model/enums/entityrarity.hpp"
#include "model/enums/weaponpassive.hpp"


using json = nlohmann::json;

dpp_async TestModule::testMessage(const dpp::slashcommand_t& event) {
    event.reply("Welcome, I am <@"+std::to_string(event.command.application_id)+">, i'm a Discord bot made in pure C++!");
	unsigned long long cur_channel = event.command.channel.id;
	dpp::cluster *bot = event.owner;

	// ------------------------------------------------------

	dpp::message msg(cur_channel,"Dump de toute la banque d'emojis");
	co_await safe_coro(bot->co_message_create(msg));
	dpp::confirmation_callback_t co_event = co_await safe_coro(bot->co_application_emojis_get());
	if(co_event.is_error()) {
		log(co_event.get_error().human_readable,true,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);
		co_return;
	}
	dpp::emoji_map emojis = get<dpp::emoji_map>(co_event.value);
	std::stringstream ss;
	for(const auto& [snowflake_id, emoji] : emojis) {
		ss << emoji.get_mention();
		//ss << parseEmoji(snowflake_id,emoji.name,emoji.is_animated()) << ' ';
	}
	co_await safe_coro(bot->co_message_create({cur_channel, ss.str()}));

	// ------------------------------------------------------

	SQLite3::Cursor cur = SQLite3::Connection::inst()->cursor();
	std::string exec = R"(
select
	w.id,
	w.entity_id,
	w.type,
	wT.name as "wTname",
	e.rarity,
	e.name,
	w.relicSlots,
	w.overloadCharge,
	w.overloadCooldown,
	w.baseATK,
	w.incrementATK,
	w.passive,
	w.basePassive,
	w.incrementPassive,
	w.effectOverall,
	w.overloadOverall
from
	weapon w join entity e on e.id = w.entity_id
			 join Enum_weapon_Type wT on wT.id = w.type
order by w.id ASC
limit 1	
;
)";

	auto query = cur.execute(exec)->fetchone();
	if(query.empty()){
		log("Query is empty, stopping from here... :(",true,logSystem::LSLevel::ERROR,logSystem::LSDirectory::DISCORD);
		co_await bot->co_message_create({cur_channel, "Query is empty, stopping from here... :("});
		co_return;
	}
	json j;
	j << SQLtoJSONobject{cur.getColumns(),query};

	dpp::embed e;

	std::string relics;
	int nbslots = j["relicSlots"].get<int>();
	auto slot = emojis[1526624674690109630];
	for(int i = 0; i < nbslots; i++){
		relics += slot.get_mention();
	}

	std::string passive;
	for(const auto& snowflake : getEmojisSnowflakesFromPassive(static_cast<WeaponPassive>(j["passive"].get<int>()))) {
		passive += emojis[snowflake].get_mention();
	}

	e.set_color(0xFF0000)
	.set_thumbnail(getUrlIconFromWeaponType(static_cast<WeaponType>(j["type"].get<int>())))
	.set_title("Dump d'arme : "+j["name"].get<std::string>())
	.add_field("Rareté","```ansi\n"+ansi::set(getString(static_cast<EntityRarity>(j["rarity"].get<double>())),getAnsiFromRarity(static_cast<EntityRarity>(j["rarity"].get<double>())),ansi::fmt::BOLD)+"\n```")
	.add_field("Slots de Reliques",relics,true)
	.add_field("Type",getEnumString(static_cast<WeaponType>(j["type"].get<int>())),true)
	.add_field("Passif",passive, true)
	.add_field("Attaque de base",std::to_string(j["baseATK"].get<int>()) + " (+" +std::to_string(j["incrementATK"].get<int>())+ " / niveau)",true)
	.add_field("Énergie nécessaire pour Surcharge",std::to_string(j["overloadCharge"].get<int>()) + " units",true)
	.add_field("Temps de recharge",std::to_string(j["overloadCooldown"].get<int>())+" tours",true)
	.add_field("Effet de l'arme","```ansi\n"+j["effectOverall"].get<std::string>()+"\n```")
	.add_field("Effet de la surcharge","```ansi\n"+j["overloadOverall"].get<std::string>()+"\n```");
	dpp::message msg2(cur_channel,"Dump d'exemple d'une arme (oui ça me fait bosser les embeds et alors ?)");
	msg2.add_embed(e);
	co_await safe_coro(bot->co_message_create(msg2));

	co_return;
}
