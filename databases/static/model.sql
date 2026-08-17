

create table Enum_entity_Type (
	id		INTEGER	primary key	AUTOINCREMENT,
	name	TEXT	not null
);

create table Enum_entity_Rarity (
	id		INTEGER	primary key	AUTOINCREMENT,
	name	TEXT	not null
);

create table entity (
	id			INTEGER					primary key AUTOINCREMENT,
	type		SMALLINT				not null	references Enum_entity_Type(id),
	name		TEXT					not null,
	slug		TEXT					not null,
	rarity		INTEGER					not null	references Enum_entity_Rarity(id),
	perSlot		INTEGER		default 1	not null,
	description	TEXT					not null
);

create view View_entity as
select
	e.id as "ID",
	eT.name as "Type",
	e.slug as "Slug",
	e.name as "Name",
	eR.name as "Rarity",
	e.perSlot as "Max Qtt per Slot",
	e.description as "Description"
from
	entity e join Enum_entity_Type eT on eT.id = e.type
			 join Enum_entity_Rarity eR on eR.id = e.rarity
;

create table Enum_weapon_Passive (
	id		INTEGER	primary key	AUTOINCREMENT,
	name	TEXT	not null
);

create table Enum_weapon_Type (
	id		INTEGER	primary key	AUTOINCREMENT,
	name	TEXT	not null
);

create table weapon (
	id					INTEGER		primary key AUTOINCREMENT,
	entity_id			BIGINT		not null 	references entity(id),
	type				SMALLINT	not null	references Enum_weapon_Type(id),
	relicSlots			SMALLINT	not null,
	effectOverall		TEXT		not null,
	effect_R1			TEXT		not null,
	effect_R2			TEXT		not null,
	effect_R3			TEXT		not null,
	effect_R4			TEXT		not null,
	overloadOverall		TEXT		not null,
	overload_R1			TEXT		not null,
	overload_R2			TEXT		not null,
	overload_R3			TEXT		not null,
	overload_R4			TEXT		not null,
	overloadCharge		INTEGER		not null,
	overloadCooldown	INTEGER		not null,
	baseATK				INTEGER		not null,
	incrementATK		INTEGER		not null,
	passive				SMALLINT	not null	references Enum_weapon_Passive(id),
	basePassive			REAL		null,
	incrementPassive	REAL		null,

	constraint CK_weapon_passive_is_none check( 
												(passive = 1 
													and basePassive is null
													and incrementPassive is null
												)
												or
												(passive <> 1
													and basePassive is not null
													and incrementPassive is not null
												)
											)
);

create view View_weapon as 
select 
	w.id,
	w.entity_id as "Entity ID",
	e.name as "Name",
	wT.name as "Type",
	eR.name as "Rarity",
	w.relicSlots || ' Slots' as "Relic Slots",
	w.effectOverall as "Effect",
	w.overloadOverall as "Overload",
	w.overloadCharge || ' Energy' as "Overload Charge",
	w.overloadCooldown || ' Turns' as "Cooldown",
	w.baseATK as "Base ATK",
	'+' || w.incrementATK || '%' as "Increment ATK",
	wP.name as "Passive",
	w.basePassive as "Base Passive",
	'+' || w.incrementPassive || '%' as "Increment Passive"
from
	weapon w join entity e on e.id = w.entity_id
			 join Enum_weapon_Passive wP on wP.id = w.passive
			 join Enum_weapon_Type wT on wT.id = w.type
			 join Enum_entity_Rarity eR on eR.id = e.rarity
;

create table weapon_Type_Stats (
	id					INTEGER primary key references Enum_weapon_Type(id),
	shortRangeDMGMult	REAL	not null,
	midRangeDMGMult		REAL	not null,
	longRangeDMGMult	REAL	not null
);

create view View_weapon_Type_Stats as
select
	wT.name as "Weapon Type",
	'x' || wTS.shortRangeDMGMult as "Short Range DMG",
	'x' || wTS.midRangeDMGMult as "Middle Range DMG",
	'x' || wTS.longRangeDMGMult as "Long Range DMG"
from
	weapon_Type_Stats wTS join Enum_weapon_Type wT on wT.id = wTS.id
;

create table Enum_effect_Stat (
	id		INTEGER	primary key,
	name	TEXT	not null
);

create table Enum_effect_listener (
	id		INTEGER	primary key,
	name	TEXT	not null
);

create table Enum_effect_modifier (
	id		INTEGER	primary key,
	name	TEXT	not null
);

create table effect (
	id					INTEGER						primary key	AUTOINCREMENT,
	entity_id			BIGINT 						not null 	references entity(id),
	name				TEXT						not null,
	description			TEXT						not null,
	icon_url			TEXT						not null,
	is_global			BOOLEAN						not null,

	listener			INTEGER		 				not null	references Enum_effect_listener(id),
	refinement_level	SMALLINT					not null,
	max_stack			INTEGER		default 1		not null,
	turns_lasting		INTEGER		default 1		not null,
	modifier			INTEGER						not null	references Enum_effect_modifier(id),
	modified_stat		INTEGER						not null	references Enum_effect_Stat(id),
	modifier_type		TEXT						not null,
	value				REAL 		default 1.0		not null,
	target_stat			INTEGER						null		references Enum_effect_Stat(id),
	cancel_after_flag	INTEGER						null,

	target_cond_1		INTEGER						null,
	operator_cond_1		INTEGER						null,
	value_cond_1		REAL						null,
	separator_cond		INTEGER						null,
	target_cond_2		INTEGER						null,
	operator_cond_2		INTEGER						null,
	value_cond_2		REAL						null

	constraint CK_effect_refinment_bounds check(refinement_level between 1 and 4),
	constraint CK_effect_maxStack_positive check(max_stack > 0),
	constraint CK_effect_turns_lasting_positive check(turns_lasting > 0),
	constraint CK_effect_conditions_validation check(
		(
			( target_cond_1 is null and operator_cond_1 is null and value_cond_1 is null )
			and
			( separator_cond is null )
			and
			( target_cond_2 is null and operator_cond_2 is null and value_cond_2 is null )
		)
		or
		(
			( target_cond_1 is not null and operator_cond_1 is not null and value_cond_1 is not null )
			and
			( separator_cond is null )
			and
			( target_cond_2 is null and operator_cond_2 is null and value_cond_2 is null )
		)
		or
		(
			( target_cond_1 is not null and operator_cond_1 is not null and value_cond_1 is not null )
			and
			( separator_cond is not null )
			and
			( target_cond_2 is not null and operator_cond_2 is not null and value_cond_2 is not null )
		)
	)

	-- constraint CK_effect_listener check(upper(listener) in( 'ON_USE','ON_TURN_START','ON_TURN_END','ON_WEAPON_SWITCH','ON_EQUIPPED','ON_NON_EQUIPPED','ON_CRIT','ON_NON_CRIT',
	-- 														'ON_HEAL','ON_HEALTH_INCREASE','ON_HEALTH_DECREASE','ON_HEALTH_CHANGED','ON_DEFEAT','ON_HEALTH_FULL',
	-- 														'BEFORE_ATTACK',		'BEFORE_BLOCK',			'BEFORE_DODGE',			'BEFORE_COUNTER',		'BEFORE_GRAB',
	-- 														'ON_ATTACK',			'ON_BLOCK',				'ON_DODGE',				'ON_COUNTER',			'ON_GRAB',
	-- 														'ON_NON_ATTACK',		'ON_NON_BLOCK',			'ON_NON_DODGE',			'ON_NON_COUNTER',		'ON_NON_GRAB',
	-- 														'AFTER_SUCCESS_ATTACK',	'AFTER_SUCCESS_BLOCK',	'AFTER_SUCCESS_DODGE',	'AFTER_SUCCESS_COUNTER','AFTER_SUCCESS_GRAB',
	-- 														'AFTER_FAILED_ATTACK',	'AFTER_FAILED_BLOCK',	'AFTER_FAILED_DODGE',	'AFTER_FAILED_COUNTER',	'AFTER_FAILED_GRAB'
	-- 													   )),

	-- constraint CK_effect_target_stat check(  upper(target_stat) in( 'ATK','DEF','VIT',                                    -- Base Stats
	-- 																'HP', 'AP','OVERLOAD_CHARGE'                          -- Variable stats
	-- 																'STA','INT',                                          -- Extra Stats
	-- 																'SHORT_RANGE_DMG','MID_RANGE_DMG','LONG_RANGE_DMG'    -- Bonus Stats
	-- 																)),
	
	-- constraint CK_effect_operator check(lower(operator) in('add','sub','mult','div','mod','set')),

	-- constraint CK_effect_cond_target_1 check(upper(cond_target) in( 'ATK','DEF','VIT',										-- Base Stats
	-- 																'HP', 'AP','OVERLOAD_CHARGE','ACTION','OPPONENT_ACTION'	-- Variable stats
	-- 																'STA','INT',											-- Extra Stats
	-- 																'SHORT_RANGE_DMG','MID_RANGE_DMG','LONG_RANGE_DMG'		-- Bonus Stats
	-- 																) or cond_target is null),

	-- constraint CK_effect_cond_operator_1 check(lower(cond_operator) in('eq','gt','lt','gte','lte','neq')),
);

create table ennemy (
	id					INTEGER 	primary key AUTOINCREMENT,
	name				TEXT		not null,
	reroll_times		INTEGER		not null,

	base_hp				INTEGER		not null,
	bonus_hp_per_level	REAL		not null,
	base_atk			INTEGER		not null,
	bonus_atk_per_level	REAL		not null,
	base_spd			INTEGER		not null,
	bonus_spd_per_level	REAL		not null,
	base_def			INTEGER		not null,
	bonus_def_per_level	REAL		not null,

	weight_attack		REAL		not null,
	weight_block		REAL		not null,
	weight_grab			REAL		not null,
	weight_dodge		REAL		not null,
	weight_counter		REAL		not null
);

create table loot_table (
	id			INTEGER		primary key AUTOINCREMENT,
	ennemy_id	INTEGER		not null 	references ennemies(id),
	entity_id	INTEGER		not null	references entity(id),
	weight		REAL		not null,
	quantity	INTEGER		not null
);

create table positions (
	id		INTEGER		primary key,
	name	TEXT		not null
);

create table positions_travel (
	id			INTEGER		primary key AUTOINCREMENT,
	base_place	INTEGER		not null references positions(id),
	directions	INTEGER		not null references positions(id)
);
