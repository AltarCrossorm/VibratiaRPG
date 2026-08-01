

insert into ennemies (name, reroll_times, base_hp, bonus_hp_per_level, base_atk, bonus_atk_per_level, base_spd, bonus_spd_per_level, base_def, bonus_def_per_level, weight_attack, weight_block, weight_grab, weight_dodge, weight_counter)
values (
	"Sanglier",
	5,
	30,
	1.05,
	8,
	1.5,
	100,
	1.2,
	50,
	1.3,

	50,
	10,
	0,
	10,
	0
);

insert into loot_table (ennemy_id, entity_id, weight, quantity)
select
	ss.seq, e.id, 5, 1
from
	entity e, sqlite_sequence ss
where
	ss.name = 'ennemies' and
	e.slug = 'beginners_blade'
;

insert into loot_table (ennemy_id, entity_id, weight, quantity)
select
	ss.seq, e.id, 20, 5
from
	entity e, sqlite_sequence ss
where
	ss.name = 'ennemies' and
	e.slug = 'raw_steak'
;

insert into loot_table (ennemy_id, entity_id, weight, quantity)
select
	ss.seq, e.id, 50, 3
from
	entity e, sqlite_sequence ss
where
	ss.name = 'ennemies' and
	e.slug = 'raw_steak'
;

insert into loot_table (ennemy_id, entity_id, weight, quantity)
select
	ss.seq, e.id, 50, 1
from
	entity e, sqlite_sequence ss
where
	ss.name = 'ennemies' and
	e.slug = 'raw_steak'
;

.print "Sanglier Inserted!"
