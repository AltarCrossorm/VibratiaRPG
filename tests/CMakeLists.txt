cmake_minimum_required(VERSION 3.14)
project(DiscordRPGTests)

include(FetchContent)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
    -std=c++26
    -Wall
    -Werror
    -Wextra
)

find_package(SQLite3 REQUIRED)

FetchContent_Declare(
    json 
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
    SYSTEM
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(DiscordRPGTests
    ../src/logSystem.cpp
    unit/sqlite3_test.cpp
)

target_include_directories(DiscordRPGTests PRIVATE 
    ../include
    ${SQLite3_INCLUDE_DIRS}
)

target_link_libraries(DiscordRPGTests
    gtest_main
    ${SQLite3_LIBRARIES}
    nlohmann_json::nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(DiscordRPGTests)
