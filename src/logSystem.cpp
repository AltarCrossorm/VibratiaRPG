#include "logSystem.hpp"
/**
 * @file logSystem.cpp
 * @date 03/06/2026
 * @authors
 *      - CRESP Enguerran
 * @brief Logging method used to log in files every activity made (depends of the developer using it.)
 *
 * @ai AI was partially used in this file for :
 * 		 - Time gathering
 * 		 - Paths (used a base made by AI then continued by a human)
 * 		 - Debugging
 * 		The code itself was entierly thought by a human and most of the code is written by a human.
 *
 * Comments and Documentation and Documentation are here to help the developers who come after.
 */
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include "config.hpp"

namespace fs = std::filesystem;

/**
 * @fn log
 * @param message The message printed into the file (after time and state)
 * @param printSTDOUT Defines weather the prompt is printed into the standart output or not. Defaults to true
 * @param logType Defines the type of log tag/state (INFO,ERROR,CRITICAL,etc...). Defaults to INFO
 * @param directoryType Says where the log will be sorted, first by year, then month, then @p directoryType, then by day of the month. Defaults to NONE
 */
void log(const std::string message, bool printSTDOUT, logSystem::LSLevel logType, logSystem::LSDirectory directoryType) {
	
	// Get actual time
	auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* ltm = std::localtime(&now);

	// Get time string
	std::ostringstream oss_year, oss_month, oss_day, oss_full_date;
	oss_year << std::put_time(ltm, "%Y");
	oss_month << std::put_time(ltm, "%m");
	oss_day << std::put_time(ltm, "%d");
	oss_full_date << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");

	std::string logtag, dirtag;
	fs::path dir_path = fs::path(ROOT_DIRECTORY) / "logs";

	switch(logType) {
	case logSystem::LSLevel::TRACE:
		logtag = "TRACE";
		break;
	case logSystem::LSLevel::DEBUG:
		logtag = "DEBUG";
		break;
	case logSystem::LSLevel::INFO:
		logtag = "INFO";
		break;
	case logSystem::LSLevel::WARNING:
		logtag = "WARNING";
		break;
	case logSystem::LSLevel::ERROR:
		logtag = "ERROR";
		break;
	case logSystem::LSLevel::CRITICAL:
		logtag = "CRITICAL";
		break;
	case logSystem::LSLevel::FATAL:
		logtag = "FATAL";
		break;
	default:
		logtag = "unhandheld";
	}

	dir_path /= oss_year.str();
	dir_path /= oss_month.str();

	switch(directoryType) {
    case logSystem::LSDirectory::ADVENTURE:
        dir_path /= "adventure";
        dirtag = "ADVENTURE";
        break;
    case logSystem::LSDirectory::EXPERIENCE:
        dir_path /= "experience";
        dirtag = "EXPERIENCE";
        break;
    case logSystem::LSDirectory::FIGHTS:
        dir_path /= "fights";
        dirtag = "FIGHTS";
        break;
    case logSystem::LSDirectory::SHOPS:
        dir_path /= "shops";
        dirtag = "SHOPS";
        break;
    case logSystem::LSDirectory::INVENTORIES:
        dir_path /= "inventories";
        dirtag = "INVENTORIES";
        break;
    case logSystem::LSDirectory::DISCORD:
        dir_path /= "discord";
        dirtag = "DISCORD";
        break;
    case logSystem::LSDirectory::NONE:
    default:
        dir_path /= "none";
        dirtag = "NONE";
    }

	// Openeing/Making file and/or directories
	try {
		if (!fs::exists(dir_path)) {
			fs::create_directories(dir_path);
		}
	} catch (const fs::filesystem_error& e) {
		std::cerr << "Erreur lors de la création des dossiers : " << e.what() << std::endl;
		return;
	}

	std::string filename = "_log_" + oss_year.str() + "-" + oss_month.str() + "-" + oss_day.str() + ".log";
	fs::path file_path = dir_path.c_str() + filename;

	std::ofstream log_file(file_path, std::ios::app);
	if (log_file.is_open()) {
		log_file << "[" << oss_full_date.str() << "]\t [" << dirtag << "] - [" << logtag << "]\t| " << message << "\n";
	} else {
		std::cerr << "Impossible d'ouvrir le fichier de log." << std::endl;
	}

	if (printSTDOUT)
	{
		std::cout << "[" << oss_full_date.str() << "]\t [" << dirtag << "] - [" << logtag << "]\t| " << message << std::endl;
	}
	// log_file automatically closes in his destructor when reaching end of scope
}
