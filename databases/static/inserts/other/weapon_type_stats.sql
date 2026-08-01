
-- The total multiplier values must not exceed 3.9

-- Inserts SWORD multipliers
insert into weapon_Type_Stats
select
	wT.id,
	1.3,
	1.3,
	1.3
from Enum_weapon_Type wT where wT.name = 'SWORD';

-- Inserts SABER multipliers
insert into weapon_Type_Stats
select
	wT.id,
	1.5,
	1.4,
	1.0
from Enum_weapon_Type wT where wT.name = 'SABER';

-- Inserts LONGSWORD multipliers
insert into weapon_Type_Stats
select
	wT.id,
	1.0,
	1.6,
	1.3
from Enum_weapon_Type wT where wT.name = 'LONGSWORD';

-- Inserts GREATSWORD multipliers
insert into weapon_Type_Stats
select
	wT.id,
	0.8,
	1.5,
	1.6
from Enum_weapon_Type wT where wT.name = 'GREATSWORD';

-- Inserts MACHETTE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	1.7,
	1.7,
	0.5
from Enum_weapon_Type wT where wT.name = 'MACHETTE';

-- Inserts DAGGER multipliers
insert into weapon_Type_Stats
select
	wT.id,
	3.2,
	0.7,
	0
from Enum_weapon_Type wT where wT.name = 'DAGGER';

-- Inserts HORNBLADE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	2.5,
	1.5,
	0
from Enum_weapon_Type wT where wT.name = 'HORNBLADE';

-- Inserts SHORTAXE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	1.2,
	2.7,
	0
from Enum_weapon_Type wT where wT.name = 'SHORTAXE';

-- Inserts GREATDOUBLEAXE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	0.1,
	1.5,
	2.3
from Enum_weapon_Type wT where wT.name = 'GREATDOUBLEAXE';

-- Inserts SPEAR multipliers
insert into weapon_Type_Stats
select
	wT.id,
	0.1,
	0.3,
	3.5
from Enum_weapon_Type wT where wT.name = 'SPEAR';

-- Inserts MACE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	0.7,
	2.7,
	0.5
from Enum_weapon_Type wT where wT.name = 'MACE';

-- Inserts WARHAMMER multipliers
insert into weapon_Type_Stats
select
	wT.id,
	0.1,
	0.2,
	3.6
from Enum_weapon_Type wT where wT.name = 'WARHAMMER';

-- Inserts MOONBLADE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	0.3,
	2.5,
	1.1
from Enum_weapon_Type wT where wT.name = 'MOONBLADE';

-- Inserts KNUCKLE multipliers
insert into weapon_Type_Stats
select
	wT.id,
	3.9,
	0,
	0
from Enum_weapon_Type wT where wT.name = 'KNUCKLE';
