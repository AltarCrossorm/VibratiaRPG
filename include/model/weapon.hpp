#pragma once
/**
 * @file weapon.hpp
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
#include "enums/weapontype.hpp"
#include "enums/weaponpassive.hpp"


struct Weapon
{
	long long id;
	int entity_id;
	WeaponType type;
	short relicSlots;
	std::string effectOverall;
	std::string effect_r1;
	std::string effect_r2;
	std::string effect_r3;
	std::string effect_r4;
	std::string overloadOverall;
	std::string overload_r1;	
	std::string overload_r2;	
	std::string overload_r3;
	std::string overload_r4;
	int overloadCharge;
	int overloadCooldown;
	int baseATK;
	int incrementATK;
	WeaponPassive passive;
	float basePassive;
	float incrementPassive;
};
