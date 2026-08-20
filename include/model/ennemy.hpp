#pragma once
/**
 * @file ennemy.hpp
 * @date 2026/08/13
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

#include "_base.hpp"


struct Ennemy final : public ORM_BASE
{
	std::string name;
	int reroll_times;

	int base_hp;
	float bonus_hp_per_level;
	int base_atk;
	float bonus_atk_per_level;
	int base_spd;
	float bonus_spd_per_level;
	int base_def;
	float bonus_def_per_level;

	float weight_attack;
	float weight_block;
	float weight_grab;
	float weight_dodge;
	float weight_counter;

	DECLARE_ORM_METADATA(Ennemy, id, name, reroll_times, base_hp, bonus_hp_per_level, base_atk, bonus_atk_per_level, base_spd, bonus_spd_per_level, base_def, bonus_def_per_level, weight_attack, weight_block, weight_grab, weight_dodge, weight_counter)
};

class EnnemyRepository final : public Repository<Ennemy>
{
public:
	virtual std::string getTableName() override {
		return "ennemy";
	}

	virtual Ennemy buildObject(std::vector<RowValue> val) override {
		BUILD_OBJECT_START(Ennemy,val)

		BUILD_OBJECT_ADD_FIELD(name,std::string)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(reroll_times,int)

		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(base_hp,int)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(bonus_hp_per_level,float)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(base_atk,int)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(bonus_atk_per_level,float)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(base_spd,int)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(bonus_spd_per_level,float)
		BUILD_OBJECT_ADD_FIELD_WITH_INT_CAST(base_def,int)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(bonus_def_per_level,float)
		
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(weight_attack,float)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(weight_block,float)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(weight_grab,float)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(weight_dodge,float)
		BUILD_OBJECT_ADD_FIELD_WITH_FLOAT_CAST(weight_counter,float)

		BUILD_OBJECT_END
	}
};
