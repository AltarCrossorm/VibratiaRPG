
insert into entity (type, name, slug, rarity, description) 
select 
	eT.id, 
	'Origine de la vie',
	'origin_of_life',
	eR.id,
	''
from
	Enum_entity_Type eT,
	Enum_entity_Rarity eR
where
	eT.name = 'WEAPON' and
	eR.name = 'LEGENDARY'
;

insert into weapon (entity_id, type, relicSlots, effectOverall, effect_R1, effect_R2, effect_R3, effect_R4, overloadOverall, overload_R1, overload_R2, overload_R3, overload_R4, overloadCharge, overloadCooldown, baseATK, incrementATK, passive, basePassive, incrementPassive) 
select 
	last_insert_rowid(),
	wT.id,
	4,	
	'Augmente les PVs de 20/25/30/40% et augmente l''ATK d''une valeur de [1;32m1,8/2/2,2/2,8%[0;0m des PVs MAX',
	'Augmente les PVs de 20% et augmente l''ATK d''une valeur de [1;32m1,8%[0;0m des PVs MAX',
	'Augmente les PVs de 25% et augmente l''ATK d''une valeur de [1;32m2%[0;0m des PVs MAX',
	'Augmente les PVs de 30% et augmente l''ATK d''une valeur de [1;32m2,2%[0;0m des PVs MAX',
	'Augmente les PVs de 40% et augmente l''ATK d''une valeur de [1;32m2,8%[0;0m des PVs MAX',
	'Génère des plantes grimpantes aux pieds de l''adversaire et l''entrave. L''adversaire ne se voit plus en capacité d''esquiver. Cet effet dure [1;32m1/2/3/5[0;0m tours et désactive l''effet de l''arme pendant [1;32m6/5/4/2[0;0m tours',
	'Génère des plantes grimpantes aux pieds de l''adversaire et l''entrave. L''adversaire ne se voit plus en capacité d''esquiver. Cet effet dure [1;32m1[0;0m tours et désactive l''effet de l''arme pendant [1;32m6[0;0m tours',
	'Génère des plantes grimpantes aux pieds de l''adversaire et l''entrave. L''adversaire ne se voit plus en capacité d''esquiver. Cet effet dure [1;32m2[0;0m tours et désactive l''effet de l''arme pendant [1;32m5[0;0m tours',
	'Génère des plantes grimpantes aux pieds de l''adversaire et l''entrave. L''adversaire ne se voit plus en capacité d''esquiver. Cet effet dure [1;32m3[0;0m tours et désactive l''effet de l''arme pendant [1;32m4[0;0m tours',
	'Génère des plantes grimpantes aux pieds de l''adversaire et l''entrave. L''adversaire ne se voit plus en capacité d''esquiver. Cet effet dure [1;32m5[0;0m tours et désactive l''effet de l''arme pendant [1;32m2[0;0m tours',
	150,
	12,
	47,
	11,
	wP.id,
	7.0,
	0.7
from
	Enum_weapon_Type wT,
	Enum_weapon_Passive wP
where
	wT.name = 'MOONBLADE' and
	wP.name = 'CRIT RATE'
;

.print "'Origine de la vie' inserted!"
