#pragma once
/**
 * @file characterpositions.hpp
 * @date 2026/08/09
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "_base.hpp"
#include <dpp/dispatcher.h>
#include <exception>
#include <string>
#include <tuple>


struct CharacterPositions final : public ORM_BASE
{
	long position;

	DECLARE_ORM_METADATA(CharacterPositions,id,position)
};

class CharacterPositionsRepository final : public Repository<CharacterPositions>
{
public:

	virtual std::string getTableName(void) override {
		return "characters_positions";
	}

	virtual CharacterPositions buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(CharacterPositions,val)
		BUILD_OBJECT_ADD_FIELD(position,long)
		BUILD_OBJECT_END
	}

	bool isAUserCharacterIsInChannel(std::size_t channelID, const dpp::user& user) {
		std::string initialQuery = R"(
		select 
			cp.id 
		from
			characters_positions cp 
				join characters c on c.id = cp.id
		where 
			cp.position = ? and
			c.user = ?
		;)";

		auto characters = SQLite3::Connection::inst()->cursor().execute(initialQuery,channelID, user.id.operator std::size_t())->fetchall();
		return characters.empty();
	}

	std::vector<CharacterPositions> getPositionsForCharactersOfAUser(const dpp::user& user) {
		std::string query = R"(
		select
			cp.id,
			cp.position
		from
			characters_positions cp
				join characters c on c.id = cp.id
		where
			c.user = ?
		;)";

		auto charPosList = SQLite3::Connection::inst()->cursor().execute(query, user.id.operator std::size_t())->fetchall();
		if (charPosList.empty())
			return {};
		std::vector<CharacterPositions> chaPosVec;
		for (Row &charPos : charPosList) {
			chaPosVec.push_back(this->buildObject(charPos));
		}
		return chaPosVec;
	}
};
