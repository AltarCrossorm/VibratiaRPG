
insert into entity (type, name, slug, rarity, description) 
select 
	eT.id, 
	'Lame du débutant',
	'beginners_blade',
	eR.id,
	''
from
	Enum_entity_Type eT,
	Enum_entity_Rarity eR
where
	eT.name = 'WEAPON' and
	eR.name = 'UNCOMMON'
;

insert into weapon (entity_id, type, relicSlots, effectOverall, effect_R1, effect_R2, effect_R3, effect_R4, overloadOverall, overload_R1, overload_R2, overload_R3, overload_R4, overloadCharge, overloadCooldown, baseATK, incrementATK, passive, basePassive, incrementPassive) 
select 
	last_insert_rowid(),
	wT.id,
	2,	
	'Une lame comme les autres, mais le vibratium contenu à l''intérieur lui permet d''utiliser les reliques.',
	'Une lame comme les autres, mais le vibratium contenu à l''intérieur lui permet d''utiliser les reliques.',
	'Une lame comme les autres, mais le vibratium contenu à l''intérieur lui permet d''utiliser les reliques.',
	'Une lame comme les autres, mais le vibratium contenu à l''intérieur lui permet d''utiliser les reliques.',
	'Une lame comme les autres, mais le vibratium contenu à l''intérieur lui permet d''utiliser les reliques.',
	'Le vibratium contenu dans la lame aveugle pendant 2 tours l''adversaire permettant au personnage d''attaquer à la pleine puissance, l''effet se désactive dès le changement de l''arme ou à la fin des 2 tours',
	'Le vibratium contenu dans la lame aveugle pendant 2 tours l''adversaire permettant au personnage d''attaquer à la pleine puissance, l''effet se désactive dès le changement de l''arme ou à la fin des 2 tours',
	'Le vibratium contenu dans la lame aveugle pendant 2 tours l''adversaire permettant au personnage d''attaquer à la pleine puissance, l''effet se désactive dès le changement de l''arme ou à la fin des 2 tours',
	'Le vibratium contenu dans la lame aveugle pendant 2 tours l''adversaire permettant au personnage d''attaquer à la pleine puissance, l''effet se désactive dès le changement de l''arme ou à la fin des 2 tours',
	'Le vibratium contenu dans la lame aveugle pendant 2 tours l''adversaire permettant au personnage d''attaquer à la pleine puissance, l''effet se désactive dès le changement de l''arme ou à la fin des 2 tours',
	75,
	7,
	34,
	6,
	wP.id,
	null,
	null
from
	Enum_weapon_Type wT,
	Enum_weapon_Passive wP
where
	wT.name = 'SWORD' and
	wP.name = 'NONE'
;

.print "'Lame du débutant' inserted!"
