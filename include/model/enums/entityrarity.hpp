#pragma once
/**
 * @file entityrarity.hpp
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
#include "../../ansi.hpp"

enum class EntityRarity : uint8_t
{
	COMMON = 1,
	UNCOMMON,
	RARE,
	EPIC,
	LEGENDARY,
	UNIQUE
};

std::string getString(EntityRarity er) {
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
