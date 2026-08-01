#pragma once
/**
 * @file entitytype.hpp
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
#include <cstdint>

enum class EntityType : uint8_t
{
	WEAPON = 1,
	ITEM,
	CONSUMABLE,
	RELIC,
	THROWABLE,
	INFUSER,
};

std::string getString(EntityType et) {
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
