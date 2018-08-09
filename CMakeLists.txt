cmake_minimum_required(VERSION 3.1)
include(ExternalProject)

PROJECT(kleuren)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g -O0")

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

# the kleuren test suite executable
add_executable(kleuren_test "")
set_target_properties(kleuren_test
  PROPERTIES OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/test)

# Set the proper include directories
target_include_directories(kleuren PUBLIC
  "${CMAKE_SOURCE_DIR}/inc"
  "${THIRDPARTY}/args"
)
target_include_directories(kleuren_test PUBLIC
  "${CMAKE_SOURCE_DIR}/inc"
  "${CMAKE_SOURCE_DIR}/test/thirdparty/catch"
)
target_link_libraries(kleuren_test kleuren_static)

# Add the source files from the subdirectories
include(src/CMakeLists.txt)
include(test/src/CMakeLists.txt)

# Set the proper installation directory
install(TARGETS kleuren_bin kleuren_static DESTINATION ${CMAKE_INSTALL_PREFIX})

# DEPENDENCIES
# BloomFilterTrie
ExternalProject_Add(project_bft
  GIT_REPOSITORY https://github.com/Colelyman/BloomFilterTrie
  GIT_TAG 0.9.0
  PREFIX ${THIRDPARTY}/BloomFilterTrie
  CMAKE_ARGS
  INSTALL_COMMAND "" # doesn't need to be installed system-wide, just locally
)
ExternalProject_Get_Property(project_bft install_dir)
add_library(bft STATIC IMPORTED)
set(BFT_PATH ${install_dir}/src/project_bft)
set_property(TARGET bft PROPERTY IMPORTED_LOCATION ${BFT_PATH}/bin/libbft_static.a)

# Judy array (a dependency of BloomFilterTrie)
set(JUDY_PATH ${BFT_PATH}/bin/judy-1.0.5)
set(JUDY_LIB ${JUDY_PATH}/lib/libJudy${CMAKE_SHARED_LIBRARY_SUFFIX})

# Jemalloc (a dependency of BloomFilterTrie)
set(JEMALLOC_PATH ${BFT_PATH}/bin/jemalloc-5.1.0)
set(JEMALLOC_LIB ${JEMALLOC_PATH}/lib/libjemalloc${CMAKE_SHARED_LIBRARY_SUFFIX})

include_directories(${BFT_PATH}/include 
  ${JUDY_PATH}/include
  ${JEMALLOC_PATH}/include)

add_dependencies(kleuren project_bft)
target_link_libraries(kleuren_bin bft ${JUDY_LIB} ${JEMALLOC_LIB})
target_link_libraries(kleuren_static bft ${JUDY_LIB} ${JEMALLOC_LIB})

