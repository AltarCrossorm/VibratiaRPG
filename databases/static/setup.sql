
.cd "./inserts"
-- Adds all enms values file by file
.print "--- Inserting Enums..."
.read "./insert_all_enums.sql"
.print "--- Enums inserted!"

-- Adds all entities values file by file
.print "--- Inserting all Entities"
.read "./insert_all_entities.sql"
.print "--- Entities inserted!"

.print "-- Inserting all Ennemies"
.read "./inert_all_ennemies.sql"
.print "--- Ennemies inserted"

.print "--- Inserting Misc and Others"
.read "./insert_all_other.sql"
.read "./insert_all_misc.sql"
.print "--- Misc and Others Inserted!"

.cd ".."

.print " - Printing the data inserted in each Enum -"
.print "Enum_weapon_Type"
select * from Enum_weapon_Type;
.print "Enum_weapon_Passive"
select * from Enum_weapon_Passive;
.print "Enum_entity_Type"
select * from Enum_entity_Type;
.print "Enum_entity_Rarity"
select * from Enum_entity_Rarity;

.print " - Printing the data inserted in each View -"
.print "View_entity"
select * from View_entity;
.print "View_weapon"
select * from View_weapon;
.print "View_weapon_Type_Stats"
select * from View_weapon_Type_Stats;
