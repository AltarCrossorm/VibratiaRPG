#pragma once

#include <string>

namespace logSystem {

enum class LSLevel {
	TRACE,
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CRITICAL,
	FATAL
};

using LSType = LSLevel;

enum class LSDirectory
{
	NONE,
	DISCORD,
	ADVENTURE,
	EXPERIENCE,
	FIGHTS,
	SHOPS,
	INVENTORIES,
};

struct LSExperience
{
	int userID;
	int characterID;
	int experienceAdded;
};

struct LSAdventure
{

};

struct LSFights
{

};

struct LSInventories
{

};

struct LSShops
{
	
};


}

// Human LOG
/**
 * @fn log
 * @param message The message printed into the file (after time and state)
 * @param printSTDOUT Defines weather the prompt is printed into the standart output or not. Defaults to @a true
 * @param logType Defines the type of log tag/state (INFO,ERROR,CRITICAL,etc...). Defaults to @a INFO
 * @param directoryType Says where the log will be sorted, first by year, then month, then @p directoryType, then by day of the month. Defaults to NONE
 */
void log(const std::string message,
		 bool printSTDOUT = true,
		 logSystem::LSLevel logType = logSystem::LSLevel::INFO,
		 logSystem::LSDirectory directoryType = logSystem::LSDirectory::NONE
		);


// Bot Log - Experience
void log(logSystem::LSExperience experience);

// Bot Log - Adventure
void log(logSystem::LSAdventure adventure);

// Bot Log - Fights
void log(logSystem::LSFights fights);

// Bot Log - Inventories
void log(logSystem::LSInventories inventories);

// Bot Log - Shops
void log(logSystem::LSShops shops);
