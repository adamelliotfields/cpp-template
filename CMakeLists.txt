cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0091 NEW)
project(convertunit)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(
        CMAKE_BUILD_TYPE
        Debug
        CACHE STRING "Build type"
        FORCE
    )
endif()

set_property(
    CACHE CMAKE_BUILD_TYPE
    PROPERTY STRINGS
    Debug
    Release
    RelWithDebInfo
    MinSizeRel
)

file(
    GLOB_RECURSE project_format_files
    CONFIGURE_DEPENDS
    RELATIVE ${CMAKE_SOURCE_DIR}
    include/*.hpp
    src/*.hpp
    src/*.cpp
    test/*.hpp
    test/*.cpp
)

file(
    GLOB_RECURSE project_lint_files
    CONFIGURE_DEPENDS
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.cpp
    test/*.cpp
)

list(SORT project_format_files)
list(SORT project_lint_files)

# Library
add_library(convertunit_lib INTERFACE)
target_include_directories(convertunit_lib INTERFACE include)

# Warnings (propagates compile flags to targets that link it)
add_library(project_warnings INTERFACE)
# Don't use -Wpedantic with Catch2
target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wconversion)

# Executable
add_executable(convertunit src/main.cpp)
# Apply warnings to local targets that compile sources, not the header-only library
target_link_libraries(convertunit PRIVATE convertunit_lib project_warnings CLI11::CLI11)

# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_HAVE_DOT YES)
    doxygen_add_docs(docs include src)
endif()

# Formatter
find_program(CLANG_FORMAT NAMES clang-format-22 clang-format)
if(CLANG_FORMAT)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${project_format_files}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
endif()

# Linter
find_program(CLANG_TIDY NAMES clang-tidy-22 clang-tidy)
if(CLANG_TIDY)
    add_custom_target(
        lint
        COMMAND
            ${CLANG_TIDY}
            --quiet
            -p
            ${CMAKE_BINARY_DIR}
            "--header-filter=^${CMAKE_SOURCE_DIR}/(include|src|test)/.*"
            --warnings-as-errors=*
            ${project_lint_files}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
endif()

# Dependencies
include(FetchContent)
FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.6.2
)
FetchContent_MakeAvailable(CLI11)

# Testing
include(CTest)
# Pass -DBUILD_TESTING=OFF to skip
if(BUILD_TESTING)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.15.1
    )
    FetchContent_MakeAvailable(Catch2)

    add_executable(convertunit_test test/convertunit_test.cpp)
    target_link_libraries(convertunit_test PRIVATE convertunit_lib Catch2::Catch2WithMain project_warnings)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    include(Catch)
    catch_discover_tests(convertunit_test)
endif()
