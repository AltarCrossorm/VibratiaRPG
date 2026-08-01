cmake_minimum_required(VERSION 3.28.3)

# Nom de ton projet
project(DiscordRPG)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options for special behavior
option(PROFILER "Activer le profiler pour analyser le code" OFF)
option(DEBUG "Activer les méthodes de déboggage à la compilation" OFF)

FetchContent_Declare(
    json 
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    SYSTEM
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    cpp-dotenv
    GIT_REPOSITORY https://github.com/adeharo9/cpp-dotenv.git
    GIT_TAG v0.2.0
    SYSTEM
)
FetchContent_MakeAvailable(cpp-dotenv)

FetchContent_Declare(
	dpp
	GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
	GIT_TAG v10.1.5
	SYSTEM
)
FetchContent_MakeAvailable(dpp)

find_package(SQLite3 REQUIRED)
find_package(OpenSSL REQUIRED)

# On définit l'exécutable et on liste les fichiers sources
# (Ajoute tes nouveaux fichiers .cpp ici au fur et à mesure)
add_executable(DiscordRPG 
    src/main.cpp
    src/logSystem.cpp
	src/discordhelpers.cpp
    src/managers/slashcommandmanager.cpp
    src/managers/botmanager.cpp
    src/managers/buttonmanager.cpp
	src/managers/messagemanager.cpp
    src/modules/testmodule.cpp
    src/modules/fightmodule.cpp
	src/modules/debugmodule.cpp
)


# On lie les bibliothèques à notre exécutable
target_link_libraries(DiscordRPG 
    dpp
    ${SQLite3_LIBRARIES}
    nlohmann_json::nlohmann_json
    cpp_dotenv
	pthread
	OpenSSL::Crypto
)

# 5. Inclusion des headers SQLite
# Indispensable pour que le compilateur trouve "sqlite3.h"
target_include_directories(DiscordRPG PRIVATE 
    include
    ${SQLite3_INCLUDE_DIRS}
)

# Gestion propre des options selon le compilateur
if(MSVC)
    target_compile_options(DiscordRPG PRIVATE
        /std:c++latest  # Active les fonctionnalités C++26 sous MSVC
        /W4             # Équivalent de -Wall -Wextra
        /WX             # Équivalent de -Werror (traite les warnings comme des erreurs)
    )
else()
    target_compile_options(DiscordRPG PRIVATE
        -Wall
        -Wextra
        -Werror
    )
endif()

target_compile_definitions(DiscordRPG PRIVATE
	CPPHTTPLIB_OPENSSL_SUPPORT
)

if(DEBUG)
	target_compile_definitions(DiscordRPG PRIVATE
		DEBUG_MODE_ENABLED
	)
endif()

if(PROFILER)
	target_compile_definitions(DiscordRPG PRIVATE
		PROFILER_MODE_ENABLED
	)
endif()

enable_testing()
add_subdirectory(tests)

# Optionnel : affiche un message si tout est ok
message(STATUS "DPP, OpenSSL et SQLite sont prêts à être forgés !")
