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

struct Turn final : public ORM_BASE
{
	long fight_id;
	time_t action_timestamp;
	bool opponent_first; // * `false` if it's `opponent1`who actes first, `true` if it's `opponent2`who actes first
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
};
