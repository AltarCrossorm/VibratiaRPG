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
#include "_base.hpp"
#include "ennemiespool.hpp"
#include "enums/entityrarity.hpp"
#include "enums/entitytype.hpp"
#include "sqlite3.hpp"

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
};
 