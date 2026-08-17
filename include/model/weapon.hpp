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
#include <dpp/dpp.h>

CREATE_ENUM(WeaponType, SWORD = 1, SABER, LONGSWORD, GREATSWORD, MACHETTE, DAGGER, HORNBLADE, SHORTAXE, GREATDOUBLEAXE, SPEAR, MACE, WARHAMMER, MOONBLADE, KNUCKLE)

CREATE_ENUM(WeaponPassive,NONE = 1,ENERGY_RECHARGE,CRIT_RATE,CRIT_DMG,HP,HEAL_BONUS,DEF,ATK,SPD,DMG_BONUS,)

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

	std::string getWeaponTypeString(WeaponType wt) {
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

	std::string getWeaponPassiveString(WeaponPassive wp) {
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
};
