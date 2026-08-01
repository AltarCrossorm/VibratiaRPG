#pragma once
/**
 * @file weaponpassive.hpp
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
#include <dpp/dpp.h>
#include <vector>

enum class WeaponPassive : uint8_t
{
	NONE = 1,
	ENERGY_RECHARGE,
	CRIT_RATE,
	CRIT_DMG,
	HP,
	HEAL_BONUS,
	DEF,
	ATK,
	SPD,
	DMG_BONUS,
};

std::string getEnumString(WeaponPassive wp) {
	switch (wp) {
	using enum WeaponPassive;
	case NONE:				return "NONE";
	case ENERGY_RECHARGE:	return "ENERGY_RECHARGE";
	case CRIT_RATE:			return "CRIT_RATE";
	case CRIT_DMG:			return "CRIT_DMG";
	case HP:				return "HP";
	case HEAL_BONUS:		return "HEAL_BONUS";
	case DEF:				return "DEF";
	case ATK:				return "ATK";
	case SPD:				return "SPD";
	case DMG_BONUS:			return "DMG_BONUS";
	default:				return "UNKNOWN";
	}
}

std::vector<dpp::snowflake> getEmojisSnowflakesFromPassive(WeaponPassive wp) {
	switch (wp) {
	using enum WeaponPassive;
	case ENERGY_RECHARGE:	return {1530842575299412088, 1530842577455022251, 1530842578763645060, 1530842579984322650, 1530842581150470246, 1530842582895296664, 1530842583994208307};
	case CRIT_RATE:			return {1529475371085336766, 1529475375929888768, 1529475377720856616, 1529475378727485503};
	case CRIT_DMG:			return {1530842037145047122, 1530842038696673320, 1530842039963615363, 1530842041075105945};
	case HP:				return {1530842864286961674, 1530842865402515467};
	case HEAL_BONUS:		return {1530842945538887761, 1530842946620887112, 1530842947493560394, 1530842948923822210, 1530842950056284160};
	case DEF:				return {1530842288086056981, 1530842289125982340, 1530842425113972906};
	case ATK:				return {1530842196973195284, 1530842197962788864, 1530842199288451193};
	case SPD:				return {1530842770313318451, 1530842771613683712, 1530842772272185426};
	case DMG_BONUS:			return {1530842419120050299, 1530842420609286164, 1530842422458712184, 1530842423515938997};
	case NONE:				[[fallthrough]];
	default:				return {1530843081413496932, 1530843082780835993};
	}
}
