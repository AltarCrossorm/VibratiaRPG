#include "modules/debugmodule.hpp"
/**
 * @file debugmodule.cpp
 * @date 2026/07/28
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "discordhelpers.hpp"
#include "sqlite3.hpp"


dpp_async DebugModule::getInventory(const dpp::slashcommand_t & event)
{
	co_await safe_coro(event.co_reply("Command not implemented yet"));
}

dpp_async DebugModule::setCharacterPos(const dpp::slashcommand_t& event)
{
	SQLite3::Cursor cur = SQLite3::Connection::inst()->cursor();

	long id = std::get<long>(event.get_parameter("id"));

	

	std::string mockCharacterMaker = R"(
	insert into characters)";

	std::string updateQuery = R"(
	update
		characters_positions
	set
		position = ?
	where
		id = ?
	;)";

	cur.execute(updateQuery,event.command.channel_id,id);

	co_await safe_coro(event.co_reply("Command not implemented yet"));
}
