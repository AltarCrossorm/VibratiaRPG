#pragma once
/**
 * @file character.hpp
 * @date 2026/08/10
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "_base.hpp"
#include <string>
#include "sqlite3.hpp"

struct Character final : public ORM_BASE
{
	long user;
	std::string name;
	std::optional<std::string> character_tupper_start;
	std::optional<std::string> character_tupper_end;

	DECLARE_ORM_METADATA(Character,id,user,name,character_tupper_start,character_tupper_end)
};

class CharacterRepository final : public Repository<Character>
{
public:

	virtual std::string getTableName(void) override {
		return "characters";
	}

	virtual Character buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Character,val)
		BUILD_OBJECT_ADD_FIELD(user,long)
		BUILD_OBJECT_ADD_FIELD(name,std::string)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL(character_tupper_start,std::string)
		BUILD_OBJECT_ADD_FIELD_OPTIONAL(character_tupper_end,std::string)
		BUILD_OBJECT_END
	}
};
