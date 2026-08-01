

-- Adds all enums values file by file
.cd "./enums"

.read "./entity_type.sql"
.read "./weapon_type.sql"
.read "./weapon_passive.sql"
.read "./entity_rarity.sql"

.cd ".."
