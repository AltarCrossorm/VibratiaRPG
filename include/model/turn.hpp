#pragma once
/**
 * @file turn.hpp
 * @date 2026/08/14
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include "_base.hpp"
#include <dpp/dpp.h>

CREATE_ENUM(TurnDistance,CLOSE,MIDDLE,FAR,OUT_OR_REACH)

struct Turn final : public ORM_BASE
{
	long fight_id;
	time_t action_timestamp;
	bool opponent_first; // * `false` if it's `opponent1` who actes first, `true` if it's `opponent2` who actes first (must be PvP)
	TurnDistance distance;
	std::optional<long> action_first;
	std::optional<long> action_second;
	std::optional<long> bonus_action;

	DECLARE_ORM_METADATA(Turn,fight_id,action_timestamp,opponent_first,action_first,action_second,bonus_action)
};

class TurnRepository final: public Repository<Turn>
{
	virtual std::string getTableName(void) override {
		return "turn";
	}

	virtual Turn buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Turn,val)
		BUILD_OBJECT_ADD_FIELD(fight_id,long)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(action_timestamp,time_t)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(opponent_first,bool)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(distance,TurnDistance)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL(action_first,long)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL(action_second,long)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL(bonus_action,long)
		BUILD_OBJECT_END
	}

	int getNumberOfTurns(long fightID) {
		std::string query = R"(
		select 
			count(*)
		from
			turn
		where
			fight_id = ?
		;)";

		auto res = SQLite3::Connection::inst()->cursor().execute(query,fightID)->fetchone();
		if(res.empty())
			return 0;
		else
			return GET_SQLITE3_VALUE<long>(res[0]);
	}

	std::optional<bool> getWhichOpponentFromTurn(dpp::user user, long turnID) {
		std::string query = R"(
		select
			f.opponent1, f.opponent2
		from 
			fight f 
				join turn t on f.id = t.fight_id
		where
			t.id = ?
			
		;)";

		auto res = SQLite3::Connection::inst()->cursor().execute(query,turnID)->fetchone();
		if(res.empty()) [[unlikely]]
			return std::nullopt;
		else [[likely]]{
			long op1 = GET_SQLITE3_VALUE<long>(res[0]);
			long op2 = GET_SQLITE3_VALUE<long>(res[1]);
			if (op1 == user.id)
				return std::make_optional<bool>(false);
			else if (op2 == user.id)
				return std::make_optional<bool>(true);
			else
				return std::nullopt;
		}
	}

	std::optional<Turn> getLastTurnFromChannel(long channelID) {
		std::string query = R"(
		select 
			t.id
		from
			turn t
				join fight f on f.id = t.fight_id
		where
			f.channel_id = ?
		;)";

		auto res = SQLite3::Connection::inst()->cursor().execute(query,channelID)->fetchone();
		if(res.empty())
			return std::nullopt;
		
		else
			return std::make_optional<Turn>(this->findById(GET_SQLITE3_VALUE<long>(res[0])).value());
	}
};
