#include "sqlite3.hpp"
/**
 * @file sqlite.cpp
 * @date 2026/08/08
 * @authors
 *      - 
 * @brief 
 *
 * @ai
 *
 * Comments and Documentation are here to help the developers who come after.
 */

SQLite3::Connection* SQLite3::Connection::instance = nullptr;

SQLite3::Connection* SQLite3::Connection::inst(void) {
	return instance;
}
