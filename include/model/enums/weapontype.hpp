#pragma once
/**
 * @file weapontype.hpp
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

enum class WeaponType : uint8_t
{
	SWORD = 1,
	SABER,
	LONGSWORD,
	GREATSWORD,
	MACHETTE,
	DAGGER,
	HORNBLADE,
	SHORTAXE,
	GREATDOUBLEAXE,
	SPEAR,
	MACE,
	WARHAMMER,
	MOONBLADE,
	KNUCKLE,
};

std::string getEnumString(WeaponType wt) {
	switch (wt) {
	using enum WeaponType;
	case SWORD: 			return "SWORD";
	case SABER: 			return "SABER";
	case LONGSWORD: 		return "LONGSWORD";
	case GREATSWORD: 		return "GREATSWORD";
	case MACHETTE: 			return "MACHETTE";
	case DAGGER: 			return "DAGGER";
	case HORNBLADE: 		return "HORNBLADE";
	case SHORTAXE: 			return "SHORTAXE";
	case GREATDOUBLEAXE:	return "GREATDOUBLEAXE";
	case SPEAR: 			return "SPEAR";
	case MACE:				return "MACE";
	case WARHAMMER: 		return "WARHAMMER";
	case MOONBLADE: 		return "MOONBLADE";
	case KNUCKLE: 			return "KNUCKLE";
	default:				return "UNKNOWN";
	}
}

std::string getUrlIconFromWeaponType(WeaponType wt) {
	std::string base = "https://cdn.discordapp.com/emojis/",
				final = ".webp?size=64&quality=lossless";
	switch (wt) {
	using enum WeaponType;
	case SWORD: 			return base + "1510358959498727444" + final;
	case SABER: 			return base + "1510358961851863080" + final;
	case LONGSWORD: 		return base + "1510358956827082874" + final;
	case GREATSWORD: 		return base + "1510358952095776799" + final;
	case MACHETTE: 			return base + "1510358939139707131" + final;
	case DAGGER: 			return base + "1510358937650597988" + final;
	case HORNBLADE: 		return base + "1510358935511764993" + final;
	case SHORTAXE: 			return base + "1510358950392889424" + final;
	case GREATDOUBLEAXE:	return base + "1510358942369186032" + final;
	case SPEAR: 			return base + "1510358954113241219" + final;
	case MACE:				return base + "1510358958228115658" + final;
	case WARHAMMER: 		return base + "1510358941022949558" + final;
	case MOONBLADE: 		return base + "1510358934081245245" + final;
	case KNUCKLE: 			return base + "1510358955392765952" + final;
	default:				return base + "1526624674690109630" + final;
	}
}
