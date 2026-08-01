#pragma once
/**
 * @file weaponmodule.hpp
 * @date 2026/07/07
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */
#include "ansi.hpp"

enum class WeaponType : unsigned short
{
    SWORD,
    SABER,
    LONGSWORD,
    GREATSWORD,
    MACHETTE,
    DAGGER,
    HORNBLADE,
    SHORTAXE,
    GREATDOUBLEAXE,
    MACE,
    WARHAMMER,
    MOONBLADE,
    KNUCKLE
};

enum class WeaponRarity : unsigned short
{
	UNCOMMON,
	RARE,
	EPIC
};

ansi::text getAnsiColorFromWeaponRarity(WeaponRarity rarity) {

}

struct WeaponData {
	unsigned long long id = 0;
	unsigned long long entity_id = 0;

};

class WeaponModule
{
private:
    WeaponType type;
    double closeRangeMultiplier;
    double midRangeMultiplier;
    double longRangeMultiplier;
    int refinementLevel;

    int weaponExperience;
    int weaponLevel;

protected:
    virtual double calculateDMGFromWeapon(double);
};
