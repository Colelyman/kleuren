cmake_minimum_required(VERSION 3.1)
include(ExternalProject)

PROJECT(kleuren)

set(CMAKE_CXX_STANDARD 11)

set(THIRDPARTY ${CMAKE_SOURCE_DIR}/thirdparty)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# TARGETS
# kleuren target holds each of the object files
add_library(kleuren OBJECT "")

# the kleuren executable
add_executable(kleuren_bin $<TARGET_OBJECTS:kleuren>)
set_target_properties(kleuren_bin
  PROPERTIES OUTPUT_NAME kleuren)

# the kleuren library
add_library(kleuren_static STATIC $<TARGET_OBJECTS:kleuren>)

# Set the proper include directories
target_include_directories(kleuren PUBLIC
  "${CMAKE_SOURCE_DIR}/inc"
  "${THIRDPARTY}/cxxopts/include"
)

# Add the source files from the subdirectories
include(src/CMakeLists.txt)

# Set the proper installation directory
install(TARGETS kleuren_bin kleuren_static DESTINATION ${CMAKE_INSTALL_PREFIX})

# DEPENDENCIES
# BloomFilterTrie
ExternalProject_Add(project_bft
  GIT_REPOSITORY https://github.com/Colelyman/BloomFilterTrie
  GIT_TAG 0.8.9
  PREFIX ${THIRDPARTY}/BloomFilterTrie
  CMAKE_ARGS -DCMAKE_C_FLAGS=-fpermissive
  INSTALL_COMMAND "" # doesn't need to be installed system-wide, just locally
)
ExternalProject_Get_Property(project_bft install_dir)
add_library(bft STATIC IMPORTED)
set(BFT_PATH ${install_dir}/src/project_bft)
set_property(TARGET bft PROPERTY IMPORTED_LOCATION ${BFT_PATH}/bin/libbft_static.a)
include_directories(${BFT_PATH}/include)
target_link_libraries(kleuren_bin judy jemalloc bft)
target_link_libraries(kleuren_static judy jemalloc bft)
