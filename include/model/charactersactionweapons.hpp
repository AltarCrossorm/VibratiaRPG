#pragma once
/**
 * @file characteractionweapons.hpp
 * @date 2026/08/20
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include <string>
#include "_base.hpp"
#include "character.hpp"
#include "inventory.hpp"

struct CharactersActionWeapons final : public ORM_BASE
{
	ForeignKey<Character> character;
	ForeignKey<Inventory> weapon_in_use;
	ForeignKey<Inventory> weapon_1;
	ForeignKey<Inventory> weapon_2;
	ForeignKey<Inventory> weapon_3;
	
	DECLARE_ORM_METADATA(CharactersActionWeapons, id, character, weapon_in_use, weapon_1, weapon_2, weapon_3)
};

class CharactersActionWeaponsRepository final : public Repository<CharactersActionWeapons>
{
public:
	virtual std::string getTableName(void) override {
		return "characters_action_weapons";
	}

	virtual CharactersActionWeapons buildObject(Row val) override {
		BUILD_OBJECT_START(CharactersActionWeapons,val)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(character, Character)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(weapon_in_use, Inventory)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(weapon_1, Inventory)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(weapon_2, Inventory)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(weapon_3, Inventory)
		BUILD_OBJECT_END
	}

	std::optional<CharactersActionWeapons> geteaponsOfCharacterFromCharacter(long characterID) {
		std::string query = R"(
		select 
			*
		from
			characters_action_weapons
		where
			character = ?
		;)";

		auto res = SQLite3::Connection::inst()->cursor().execute(query,characterID)->fetchone();
		if(res.empty())
			return std::nullopt;
		else
			return std::make_optional<CharactersActionWeapons>(this->findById(GET_SQLITE3_VALUE<long>(res[0])).value());
	}
};
