#pragma once
/**
 * @file inventory.hpp
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

struct Inventory final : public ORM_BASE
{
	ForeignKey<Character> character;
	ForeignKey<Entity> entity_id;
	long quantity;

	DECLARE_ORM_METADATA(Inventory, id, character, entity_id, quantity)
};

class InventoryRepository final : Repository<Inventory>
{
public:
	virtual std::string getTableName(void) override {
		return "inventory";
	}

	virtual Inventory buildObject(Row val) {
		BUILD_OBJECT_START(Inventory,val)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(character,Character)
		BUILD_OBJECT_ADD_FIELD_FOREIGN(entity_id,Entity)
		BUILD_OBJECT_ADD_FIELD(quantity,long)
		BUILD_OBJECT_END
	}
};
