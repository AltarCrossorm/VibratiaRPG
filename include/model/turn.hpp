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

#include "fights.hpp"

CREATE_ENUM(TurnDistance,CLOSE,MIDDLE,FAR,OUT_OR_REACH)
CREATE_ENUM(TurnAction, NOTHING, ATTACK, BLOCK, GRAB, COUNTER, DODGE, OVERLOAD, WEAPON_CHANGE_TO_1, WEAPON_CHANGE_TO_2, WEAPON_CHANGE_TO_3)

struct Turn final : public ORM_BASE
{
	ForeignKey<Fights> fight_id;
	time_t action_timestamp;
	bool opponent_first; // * `false` if it's `opponent1` who actes first, `true` if it's `opponent2` who actes first
	TurnDistance distance;
	std::optional<TurnAction> action_first;
	std::optional<TurnAction> action_second;
	std::optional<TurnAction> bonus_action;

	DECLARE_ORM_METADATA(Turn, id, fight_id, action_timestamp, opponent_first, action_first, action_second, bonus_action)
};

class TurnRepository final: public Repository<Turn>
{
public:
	static constexpr bool OPPONENT_1 = false;
	static constexpr bool OPPONENT_2 = true;

	virtual std::string getTableName(void) override {
		return "turn";
	}

	virtual Turn buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Turn,val)
		BUILD_OBJECT_ADD_FIELD(fight_id,long)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(action_timestamp,time_t)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(opponent_first,bool)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(distance,TurnDistance)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL_WITH_INT_CAST(action_first,TurnAction)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL_WITH_INT_CAST(action_second,TurnAction)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL_WITH_INT_CAST(bonus_action,TurnAction)
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

	std::optional<Turn> getLastTurnFromPosition(long channelID) {
		std::string query = R"(
		select 
			t.id
		from
			turn t
				join fight f on f.id = t.fight_id
		where
			f.channel_id = ? and
			f.isEnded = 0
		order by
			t.id DESC
		;)";

		auto res = SQLite3::Connection::inst()->cursor().execute(query,channelID)->fetchone();
		if(res.empty())
			return std::nullopt;
		
		else
			return std::make_optional<Turn>(this->findById(GET_SQLITE3_VALUE<long>(res[0])).value());
	}

	void updateCharacterTurn(Turn turnToUpdate, TurnAction action, bool isFirst) {
		if (isFirst) {
			if(!turnToUpdate.action_first)
				this->update(turnToUpdate.id.value(),&Turn::action_first,action);
			else
				this->update(turnToUpdate.id.value(),&Turn::bonus_action,action);
		} else {
			if(action == TurnAction::WEAPON_CHANGE_TO_1 || action == TurnAction::WEAPON_CHANGE_TO_2 || action == TurnAction::WEAPON_CHANGE_TO_3)
				this->update(turnToUpdate.id.value(),&Turn::action_second,TurnAction::NOTHING);
			else
				this->update(turnToUpdate.id.value(),&Turn::action_second,action);
		}
	}
};
