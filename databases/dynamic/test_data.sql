
delete from characters_positions;
delete from positions;
delete from characters_action_weapons;
delete from inventories;
delete from character_stats;
delete from characters;


insert into characters (user, name, character_tupper_start, character_tupper_end)
values (
	585567788400115762,
	'Albedo',
	'AC-',
	null
);

insert into character_stats (character, level, pocket_balance, resonnance_strengh, base_ATK, base_DEF, base_SPD, base_HP, base_Crit_Rate, base_Crit_DMG, base_ER)
values (
	last_insert_rowid(),
	12,
	2800,
	1,
	28,
	342,
	429,
	380,
	7.5,
	50.0,
	62.0
);

insert into inventories (character, entity_id)
select
	ss.seq,
	e.id
from
	sqlite_sequence ss,
	entity e
where
	e.slug = 'beginners_blade' and
	ss.name = 'characters'
;	

insert into characters_action_weapons (character, weapon_1)
select
	ss.seq,
	i.id
from
	sqlite_sequence ss,
	entity e join inventories i on e.id = i.entity_id
where
	e.slug = 'beginners_blade' and
	ss.name = 'characters'
;


insert into characters (user, name, character_tupper_start, character_tupper_end)
values (
	585567788400115762,
	'Dynamis',
	'Dyna_Start-',
	'-Dyna_End'
);

insert into character_stats (character, level, pocket_balance, resonnance_strengh, base_ATK, base_DEF, base_SPD, base_HP, base_Crit_Rate, base_Crit_DMG, base_ER)
values (
	last_insert_rowid(),
	12,
	2800,
	1,
	28,
	342,
	429,
	380,
	7.5,
	50.0,
	62.0
);

insert into inventories (character, entity_id)
select
	ss.seq,
	e.id
from
	sqlite_sequence ss,
	entity e
where
	e.slug = 'beginners_blade' and
	ss.name = 'characters'
;	

insert into characters_action_weapons (character, weapon_1)
select
	ss.seq,
	i.id
from
	entity e join inventories i on e.id = i.entity_id
			 join characters c on c.id = i.character
			 join sqlite_sequence ss on c.id = ss.seq
where
	e.slug = 'beginners_blade' and
	ss.name = 'characters'
;

insert into positions(id, name)
values (1532023529321791578,'Salle de test "bite"');
insert into characters_positions(id,position)
values (1,1532023529321791578);
insert into ennemies_pool(ennemy_id,position)
values (1,1532023529321791578);
