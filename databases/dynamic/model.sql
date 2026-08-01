


create table characters (
	id						INTEGER	primary key	AUTOINCREMENT,
	user					INTEGER	not null,
	character_name			TEXT	not null,
	character_tupper_start	TEXT		null,
	character_tupper_end	TEXT		null
);

create table character_stats (
	id					INTEGER				primary key AUTOINCREMENT,
	character			INTEGER				not null	references characters(id),
	level				INTEGER 			not null,
	pocket_balance		REAL	default	0	not null,

	resonnance_strengh	INTEGER				not null, -- Same purpose as Rupture effect in HSR or Elemental Mastery in Genshin

	base_ATK			INTEGER				not null,
	base_DEF			INTEGER				not null,
	base_SPD			INTEGER				not null,
	base_HP				INTEGER				not null,

	base_Crit_Rate		REAL				not null,
	base_Crit_DMG		REAL				not null,

	base_ER				REAL				not null,

	constraint CK_pocket_balance_positive check (pocket_balance > 0.0)
);

create table banks (
	id			INTEGER		primary key AUTOINCREMENT,
	name		TEXT		not null,
	owner		INTEGER			null	references characters(id)
);

create table bank_balances (
	id			INTEGER		primary key AUTOINCREMENT,
	bank		INTEGER		not null	references banks(id),
	character	INTEGER		not null	references characters(id),
	balance		REAL		not null
);

create table fights (
	id			INTEGER		primary key	AUTOINCREMENT,
	startFight	TIMESTAMP	not null,
	channelID	INTEGER		not null,
	opponnent1	TEXT		not null 	references characters(id),
	opponnent2	TEXT		not null	references characters(id),
	isEnded		BOOLEAN		not null,

	constraint CK_fights_opponents_not_same check(
		opponnent1 <> opponnent2
	)
);

create table Enum_fight_status_action (
	id		INTEGER	primary key,
	name	TEXT	not null
);

create table fight_status (
	id					INTEGER		primary key	AUTOINCREMENT,
	fight_id			INTEGER		not null	references fights(id),
	action_timestamp	TIMESTAMP	not null,
	opponent_first		BOOLEAN		not null,	-- 0 for opponent1, 1 for opponent2
	action_first		INTEGER			null	references Enum_fight_status_action(id),
	action_second		INTEGER			null	references Enum_fight_status_action(id)
);

create table inventories (
	id			INTEGER					primary key	AUTOINCREMENT,
	character	INTEGER					not null	references characters(id),
	entity_id	INTEGER					not null	references entity(id),
	quantity	INTEGER		default 1	not null
);

create table character_weapons (
	id			INTEGER		not null	references inventories(id),
	character	INTEGER		not null	references characters(id),
	entity_id	INTEGER		not null	references entity(id),

	level				INTEGER		not null,
	refinement			INTEGER		not null,
	relic_inserted_1	INTEGER			null,
	relic_inserted_2	INTEGER			null,
	relic_inserted_3	INTEGER			null,
	relic_inserted_4	INTEGER			null,
	relic_inserted_5	INTEGER			null,
	relic_inserted_6	INTEGER			null,

	constraint PK_character_weapons primary key (id, character, entity_id),
	constraint CK_character_weapon_level_is_ok check (level >= 1 and level <= 50),
	constraint CK_character_weapon_relic_ordering check (
		(relic_inserted_1 is null and relic_inserted_2 is null and relic_inserted_3 is null and relic_inserted_4 is null and relic_inserted_5 is null and relic_inserted_6 is null)
		or
		(relic_inserted_1 is not null and relic_inserted_2 is null and relic_inserted_3 is null and relic_inserted_4 is null and relic_inserted_5 is null and relic_inserted_6 is null)
		or
		(relic_inserted_1 is not null and relic_inserted_2 is not null and relic_inserted_3 is null and relic_inserted_4 is null and relic_inserted_5 is null and relic_inserted_6 is null)
		or
		(relic_inserted_1 is not null and relic_inserted_2 is not null and relic_inserted_3 is not null and relic_inserted_4 is null and relic_inserted_5 is null and relic_inserted_6 is null)
		or
		(relic_inserted_1 is not null and relic_inserted_2 is not null and relic_inserted_3 is not null and relic_inserted_4 is not null and relic_inserted_5 is null and relic_inserted_6 is null)
		or
		(relic_inserted_1 is not null and relic_inserted_2 is not null and relic_inserted_3 is not null and relic_inserted_4 is not null and relic_inserted_5 is not null and relic_inserted_6 is null)
		or
		(relic_inserted_1 is not null and relic_inserted_2 is not null and relic_inserted_3 is not null and relic_inserted_4 is not null and relic_inserted_5 is not null and relic_inserted_6 is not null)
	),
	constraint CK_character_weapon_refinement_is_ok check (refinement >= 1 and refinement <= 4)
);

create table characters_action_weapons (
	id			INTEGER		primary key	AUTOINCREMENT,
	character	INTEGER		not null	references characters(id),
	weapon_1	INTEGER			null	references inventories(id),
	weapon_2	INTEGER			null	references inventories(id),
	weapon_3	INTEGER			null	references inventories(id),

	constraint CK_character_action_weapon_ordering check (
		(weapon_1 is null and weapon_2 is null and weapon_3 is null)
		or
		(weapon_1 is not null and weapon_2 is null and weapon_3 is null)
		or
		(weapon_1 is not null and weapon_2 is not null and weapon_3 is null)
		or
		(weapon_1 is not null and weapon_2 is not null and weapon_3 is not null)
	)
);

create table ennemies_pool (
	id			INTEGER		primary key AUTOINCREMENT,
	ennemy_id	INTEGER		not null	references ennemies(id),
	channelID	INTEGER		not null
);

create table characters_positions (
	id 			INTEGER		primary key AUTOINCREMENT,
	character	INTEGER		not null 	references character(id),
	position	INTEGER		not null	references positions(id)
);
