-- SQLite3 format setup
.mode box
PRAGMA foreign_keys = ON;
.bail on

.read "./databases/dynamic/rebuild.sql"

.read "./databases/static/rebuild.sql"
