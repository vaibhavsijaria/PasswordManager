cmake_minimum_required(VERSION 3.28.0)

project(passwordManager
    VERSION 1.0
    DESCRIPTION "password manager in C"
    LANGUAGES C)

file(GLOB_RECURSE SOURCES "src/*.c")

find_package(SQLite3 REQUIRED)

add_executable(passwordManager ${SOURCES})

target_include_directories(passwordManager PRIVATE include)

target_link_libraries(passwordManager PRIVATE ${SQLite3_LIBRARIES})

target_include_directories(passwordManager PRIVATE ${SQLite3_INCLUDE_DIRS})

target_compile_features(passwordManager PRIVATE c_std_17)