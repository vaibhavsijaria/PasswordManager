cmake_minimum_required(VERSION 3.28.0)

project(passwordManager
    VERSION 1.0
    DESCRIPTION "password manager in C"
    LANGUAGES C)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(passwordManager ${SOURCES})

target_include_directories(passwordManager PRIVATE include)

# target_link_libraries()

target_compile_features(passwordManager PRIVATE c_std_17)