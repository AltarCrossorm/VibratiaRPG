
insert into entity (type, name, slug, rarity, description) 
select 
	eT.id, 
	'Cascade du savoir',
	'waterfall_of_wisdom',
	eR.id,
	''
from
	Enum_entity_Type eT,
	Enum_entity_Rarity eR
where
	eT.name = 'WEAPON' and
	eR.name = 'EPIC'
;

insert into weapon (entity_id, type, relicSlots, effectOverall, effect_R1, effect_R2, effect_R3, effect_R4, overloadOverall, overload_R1, overload_R2, overload_R3, overload_R4, overloadCharge, overloadCooldown, baseATK, incrementATK, passive, basePassive, incrementPassive) 
select 
	last_insert_rowid(),
	wT.id,
	4,	
	'Lorsque le personnage contre, son taux CRIT augmente de [1;32m8/9/10/11%[0;0m de sa recharge d''énergie, cet effet est cumulable jusqu''à 3 fois. L''effet est réinitialisé en cas de Vide ou de coup CRIT.',
	'Lorsque le personnage contre, son taux CRIT augmente de [1;32m8%[0;0m de sa recharge d''énergie, cet effet est cumulable jusqu''à 3 fois. L''effet est réinitialisé en cas de Vide ou de coup CRIT.',
	'Lorsque le personnage contre, son taux CRIT augmente de [1;32m9%[0;0m de sa recharge d''énergie, cet effet est cumulable jusqu''à 3 fois. L''effet est réinitialisé en cas de Vide ou de coup CRIT.',
	'Lorsque le personnage contre, son taux CRIT augmente de [1;32m10%[0;0m de sa recharge d''énergie, cet effet est cumulable jusqu''à 3 fois. L''effet est réinitialisé en cas de Vide ou de coup CRIT.',
	'Lorsque le personnage contre, son taux CRIT augmente de [1;32m13%[0;0m de sa recharge d''énergie, cet effet est cumulable jusqu''à 3 fois. L''effet est réinitialisé en cas de Vide ou de coup CRIT.',
	'Retire la priorité pendant 3 tours et octroie un bonus de DGT CRIT équivalent à [1;32m150/165/180/240%[0;0m du Taux CRIT',
	'Retire la priorité pendant 3 tours et octroie un bonus de DGT CRIT équivalent à [1;32m150%[0;0m du Taux CRIT',
	'Retire la priorité pendant 3 tours et octroie un bonus de DGT CRIT équivalent à [1;32m165%[0;0m du Taux CRIT',
	'Retire la priorité pendant 3 tours et octroie un bonus de DGT CRIT équivalent à [1;32m180%[0;0m du taux CRIT',
	'Retire la priorité pendant 3 tours et octroie un bonus de DGT CRIT équivalent à [1;32m240%[0;0m du taux CRIT',
	120,
	12,
	41,
	9,
	wP.id,
	7.0,
	0.6
from
	Enum_weapon_Type wT,
	Enum_weapon_Passive wP
where
	wT.name = 'GREATSWORD' and
	wP.name = 'CRIT RATE'
;

.print "'Cascade du savoir' inserted!"
