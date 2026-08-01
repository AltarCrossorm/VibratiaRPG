
insert into entity (type, name, slug, rarity, perSlot, description)
select
	eT.id,
	'Steak (cru)',
	'raw_steak',
	eR.id,
	99,
	'Un morceau de steak cru'
from
	Enum_entity_Type eT,
	Enum_entity_Rarity eR
where
	eT.name = 'ITEM' and
	eR.name = 'COMMON'
;

.print "Steak (cru) Inserted!"
