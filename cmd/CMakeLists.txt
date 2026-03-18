cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(CMAKE_C_FLAGS_RELEASE "-Os -s")

# Disable PDB generation for MSVC, as these are not needed for the command-line tools and can cause issues with distribution.
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "") 
set(CMAKE_C_FLAGS_RELEASE "/O2")

# Set the C++ standard to C++17 for all targets in this directory.
set(CMAKE_CXX_STANDARD 17)



project(octa_core_utils_cmd)

file(GLOB TOOLS "*.c")

foreach(src ${TOOLS})
    get_filename_component(name ${src} NAME_WE)
    add_executable(${name} ${src})
endforeach()

# Building Help Executable

include_directories(../docs)
add_executable(ochelp ../docs/ochelp.c)
include_directories(../other)

# Building Octacode Executable
# Using cJSON as a dependency for octacode, which is a lightweight JSON parser in C. This allows octacode to handle JSON data effectively, making it easier to work with configurations or data that may be in JSON format.
add_library(cjson STATIC
    ../ext-libs/cJSON/cJSON.c
)

target_include_directories(cjson PUBLIC
    ../ext-libs/cJSON
)

add_executable(octacode ../other/octacode.c)
target_link_libraries(octacode PRIVATE cjson)

include_directories(../other/ntop)
option(ENABLE_UNICODE "Compile with Unicode support" OFF)

if (ENABLE_UNICODE)
    add_definitions(-DUNICODE -D_UNICODE)
endif()
add_executable(htop ../other/ntop/ntop.c ../other/ntop/util.c ../other/ntop/vi.c )