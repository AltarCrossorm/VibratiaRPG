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
#include "entityrarity.hpp"
#include "entitytype.hpp"

struct Entity
{
	long long id;
	EntityType type;
	std::string name;
	std::string slug;
	EntityRarity rarity;
	int maxStack;
	std::string description;

	operator int() {
		return this->id;
	}

	operator std::string() {
		return this->slug;
	}
};
 