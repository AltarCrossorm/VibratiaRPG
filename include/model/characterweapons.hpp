#pragma once
/**
 * @file characterweapons.hpp
 * @date 2026/08/19
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
#include "entity.hpp"

struct CharacterWeapons final : public ORM_BASE
{
	ForeignKey<Character> character;
	ForeignKey<Entity> entity_id;
	short level;
	short refinement;
	long relic_inserted_1;
	long relic_inserted_2;
	long relic_inserted_3;
	long relic_inserted_4;
	long relic_inserted_5;
	long relic_inserted_6;
	
	DECLARE_ORM_METADATA(CharacterWeapons, character, entity_id, level, refinement, relic_inserted_1, relic_inserted_2, relic_inserted_3, relic_inserted_4, relic_inserted_5, relic_inserted_6)
};

class CharacterWeaponsRepository final : public Repository<CharacterWeapons>
{
public:
	virtual std::string getTableName(void) override {
		return "character_weapons";
	}
};
