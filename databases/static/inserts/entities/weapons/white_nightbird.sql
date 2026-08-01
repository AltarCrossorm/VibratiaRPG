
insert into entity (type, name, slug, rarity, description) 
select 
	eT.id, 
	'Oiseau de la nuit blanche',
	'white_nightbird',
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
	'Lorsque l''utilisateur subit des DGT après avoir raté une attaque ou s''être fait contrer une, il obtient une plume nocturne augmentant son ATK de [1;32m10/15/20/25%[0;0m par set de relique. Si un set 3 ou 4 pièce est équipé sur l''arme, le taux de recharge d''énergie augmente respectivement de [1;32m30/35/40/45[0;0m ou [1;32m40/45/50/55%[0;0m du raffinement de la relique de set la plus basse. Cet effet ne dure que jusqu''à ce que le personnage arrive à porter un coup et est réinitialisé à chaque coup raté. L''effet obtient un bonus de [1;32m20/22,5/25/27,5%[0;0m supplémentaire lorsque le porteur de l''arme passe en-dessous de [1;32m22/23/24/25%[0;0m de ses PVs MAX.',
	'Lorsque l''utilisateur subit des DGT après avoir raté une attaque ou s''être fait contrer une, il obtient une plume nocturne augmentant son ATK de [1;32m10%[0;0m par set de relique. Si un set 3 ou 4 pièce est équipé sur l''arme, le taux de recharge d''énergie augmente respectivement de [1;32m30[0;0m ou [1;32m40%[0;0m du raffinement de la relique de set la plus basse. Cet effet ne dure que jusqu''à ce que le personnage arrive à porter un coup et est réinitialisé à chaque coup raté. L''effet obtient un bonus de [1;32m20%[0;0m supplémentaire lorsque le porteur de l''arme passe en-dessous de [1;32m22%[0;0m de ses PVs MAX.',
	'Lorsque l''utilisateur subit des DGT après avoir raté une attaque ou s''être fait contrer une, il obtient une plume nocturne augmentant son ATK de [1;32m15%[0;0m par set de relique. Si un set 3 ou 4 pièce est équipé sur l''arme, le taux de recharge d''énergie augmente respectivement de [1;32m35[0;0m ou [1;32m45%[0;0m du raffinement de la relique de set la plus basse. Cet effet ne dure que jusqu''à ce que le personnage arrive à porter un coup et est réinitialisé à chaque coup raté. L''effet obtient un bonus de [1;32m22,5%[0;0m supplémentaire lorsque le porteur de l''arme passe en-dessous de [1;32m23%[0;0m de ses PVs MAX.',
	'Lorsque l''utilisateur subit des DGT après avoir raté une attaque ou s''être fait contrer une, il obtient une plume nocturne augmentant son ATK de [1;32m20%[0;0m par set de relique. Si un set 3 ou 4 pièce est équipé sur l''arme, le taux de recharge d''énergie augmente respectivement de [1;32m40[0;0m ou [1;32m50%[0;0m du raffinement de la relique de set la plus basse. Cet effet ne dure que jusqu''à ce que le personnage arrive à porter un coup et est réinitialisé à chaque coup raté. L''effet obtient un bonus de [1;32m25%[0;0m supplémentaire lorsque le porteur de l''arme passe en-dessous de [1;32m24%[0;0m de ses PVs MAX.',
	'Lorsque l''utilisateur subit des DGT après avoir raté une attaque ou s''être fait contrer une, il obtient une plume nocturne augmentant son ATK de [1;32m25%[0;0m par set de relique. Si un set 3 ou 4 pièce est équipé sur l''arme, le taux de recharge d''énergie augmente respectivement de [1;32m45[0;0m ou [1;32m55%[0;0m du raffinement de la relique de set la plus basse. Cet effet ne dure que jusqu''à ce que le personnage arrive à porter un coup et est réinitialisé à chaque coup raté. L''effet obtient un bonus de [1;32m27,5%[0;0m supplémentaire lorsque le porteur de l''arme passe en-dessous de [1;32m25%[0;0m de ses PVs MAX.',
	'Augmente la VIT de [1;32m50/52,5/55/60%[0;0m pendant 4 tours et donne la priorité au prochain coup à chaque fois que l''ancien rate. La surcharge ne fait plus effet lorsque un changement d''arme est effectué ou que 4 tours se soient écoulés',
	'Augmente la VIT de [1;32m50%[0;0m pendant 4 tours et donne la priorité au prochain coup à chaque fois que l''ancien rate. La surcharge ne fait plus effet lorsque un changement d''arme est effectué ou que 4 tours se soient écoulés',
	'Augmente la VIT de [1;32m52.5%[0;0m pendant 4 tours et donne la priorité au prochain coup à chaque fois que l''ancien rate. La surcharge ne fait plus effet lorsque un changement d''arme est effectué ou que 4 tours se soient écoulés',
	'Augmente la VIT de [1;32m55%[0;0m pendant 4 tours et donne la priorité au prochain coup à chaque fois que l''ancien rate. La surcharge ne fait plus effet lorsque un changement d''arme est effectué ou que 4 tours se soient écoulés',
	'Augmente la VIT de [1;32m60%[0;0m pendant 4 tours et donne la priorité au prochain coup à chaque fois que l''ancien rate. La surcharge ne fait plus effet lorsque un changement d''arme est effectué ou que 4 tours se soient écoulés',
	650,
	12,
	46,
	13,
	wP.id,
	9.0,
	2.5
from
	Enum_weapon_Type wT,
	Enum_weapon_Passive wP
where
	wT.name = 'SWORD' and
	wP.name = 'ENERGY RECHARGE'
;

.print "'Oiseau de la nuit blanche' inserted!"
