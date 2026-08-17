-- Drop in reverse order (to preserve foreign keys)

drop table if exists positions_travel;
drop table if exists positions;

drop table if exists loot_table;
drop table if exists ennemies;

drop table if exists effect;

drop table if exists Enum_effect_Stat;
drop table if exists Enum_fight_status_action;


drop view if exists View_weapon_Type_Stats;
drop table if exists weapon_Type_Stats;

drop view if exists View_weapon;
drop table if exists weapon;
drop table if exists Enum_weapon_Passive;
drop table if exists Enum_weapon_Type;
drop table if exists Enum_weapon_Rarity;

drop view if exists View_entity;
drop table if exists entity;
drop table if exists Enum_entity_Type;
drop table if exists Enum_entity_Rarity;
