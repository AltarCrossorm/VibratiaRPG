-- SQLite3 format setup
.mode box
PRAGMA foreign_keys = ON;
.bail on
.cd "./databases/static"

-- Delete everything (to rebuild the database)

.read "./drop.sql"
.print "--- Database is deleted"

-- Rebuild the model

.read "./model.sql"
.print "--- New model applied, populating..."

-- Then insert all the setup data

.read "./setup.sql"

.cd "../.."
