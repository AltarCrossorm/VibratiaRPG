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
#include "_base.hpp"
#include "enums/weapontype.hpp"
#include "enums/weaponpassive.hpp"


struct Weapon final : public ORM_BASE
{
	long entity_id;
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
	short overloadCooldown;
	int baseATK;
	int incrementATK;
	WeaponPassive passive;
	float basePassive;
	float incrementPassive;

	DECLARE_ORM_METADATA(Weapon,id,type,relicSlots,effectOverall, effect_r1, effect_r2, effect_r3, effect_r4, overloadOverall, overload_r1, overload_r2, overload_r3, overload_r4, overloadCharge, overloadCooldown, baseATK, incrementATK, passive, basePassive, incrementPassive)
};

class WeaponRepository final : public Repository<Weapon>
{
public:
	virtual std::string getTableName(void) override {
		return "weapon";
	}

	virtual Weapon buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Weapon,val)
		BUILD_OBJECT_ADD_FIELD(entity_id,long)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(type,WeaponType)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(relicSlots,short)
		BUILD_OBJECT_ADD_FIELD(effectOverall,std::string)
		BUILD_OBJECT_ADD_FIELD(effect_r1,std::string)
		BUILD_OBJECT_ADD_FIELD(effect_r2,std::string)
		BUILD_OBJECT_ADD_FIELD(effect_r3,std::string)
		BUILD_OBJECT_ADD_FIELD(effect_r4,std::string)
		BUILD_OBJECT_ADD_FIELD(overloadOverall,std::string)
		BUILD_OBJECT_ADD_FIELD(overload_r1,std::string)
		BUILD_OBJECT_ADD_FIELD(overload_r2,std::string)
		BUILD_OBJECT_ADD_FIELD(overload_r3,std::string)
		BUILD_OBJECT_ADD_FIELD(overload_r4,std::string)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(overloadCharge,int)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(overloadCooldown,short)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(baseATK,int)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(incrementATK,int)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(passive,WeaponPassive)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(incrementPassive,float)
		BUILD_OBJECT_END
	}
};
