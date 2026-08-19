#pragma once
/**
 * @file entity.hpp
 * @date 2026/07/23
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
#include "sqlite3.hpp"

#include "ansi.hpp"

CREATE_ENUM(EntityType, WEAPON = 1, ITEM, CONSUMABLE, RELIC, THROWABLE, INFUSER)
CREATE_ENUM(EntityRarity, COMMON = 1, UNCOMMON, RARE, EPIC, LEGENDARY, UNIQUE)

struct Entity final : public ORM_BASE
{
	EntityType type;
	std::string name;
	std::string slug;
	EntityRarity rarity;
	int maxStack;
	std::string description;

	DECLARE_ORM_METADATA(Entity,id,type,name,slug,rarity,maxStack,description)
};

class EntityRepository final : public Repository<Entity>
{
public:
	virtual std::string getTableName(void) override {
		return "entity";
	}

	virtual Entity buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Entity,val)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(type,EntityType)
		BUILD_OBJECT_ADD_FIELD(name,std::string)
		BUILD_OBJECT_ADD_FIELD(slug,std::string)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(rarity,EntityRarity)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(maxStack,int)
		BUILD_OBJECT_ADD_FIELD(description, std::string)
		BUILD_OBJECT_END
	}

	std::string getEntityTypeString(EntityType et) {
		switch(et){
		using enum EntityType;
		case WEAPON:		return "WEAPON";
		case ITEM:			return "ITEM";
		case CONSUMABLE:	return "CONSUMABLE";
		case RELIC:			return "RELIC";
		case THROWABLE:		return "THROWABLE";
		case INFUSER:		return "INFUSER";
		default:			return "UNKNOWN";
		}
	}

	std::string getEntityRarityString(EntityRarity er) {
		switch(er){
		using enum EntityRarity;
		case COMMON:	return "COMMON";
		case UNCOMMON:	return "UNCOMMON";
		case RARE:		return "RARE";
		case EPIC:		return "EPIC";
		case LEGENDARY:	return "LEGENDARY";
		case UNIQUE:	return "UNIQUE";
		default:		return "UNKNOWN";
		}
	}

	ansi::text getAnsiFromRarity(EntityRarity er) {
		switch(er) {
		using enum EntityRarity;
		case COMMON:	return ansi::txtColor::LIGHTGREY;
		case UNCOMMON:	return ansi::txtColor::GREEN;
		case RARE:		return ansi::txtColor::CYAN;
		case EPIC:		return ansi::txtColor::PINK;
		case LEGENDARY:	return ansi::txtColor::GOLD;
		case UNIQUE:	return ansi::txtColor::RED;
		default:		return ansi::txtColor::LIGHTGREY;
		}
	}
};
 