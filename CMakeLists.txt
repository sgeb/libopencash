cmake_minimum_required(VERSION 2.8.8)

set(OC_LIB_NAME opencash)
set(OC_PROJECT_NAME "lib${OC_LIB_NAME}")
project(${OC_PROJECT_NAME} CXX)

option(OC_DEBUG "Build a debug version of ${OC_PROJECT_NAME} and its dependencies (default: build a release version)." OFF)
option(OC_STATIC "Build a static version of ${OC_PROJECT_NAME} and its dependencies (default: build a dynamic/shared version)." OFF)
option(OC_TESTS "Build all of ${OC_PROJECT_NAME}'s unit tests (default: OFF; except when OC_DEBUG was enabled, then it is always ON)." OFF)

if(OC_DEBUG)
  set(CMAKE_BUILD_TYPE "Debug")
  set(OC_TESTS ON)
else()
  set(CMAKE_BUILD_TYPE "Release")
endif(OC_DEBUG)

if(OC_STATIC)
  set(BUILD_SHARED_LIBS OFF)
else()
  set(BUILD_SHARED_LIBS ON)
endif(OC_STATIC)

message(STATUS "OC_DEBUG: ${OC_DEBUG}")
message(STATUS "OC_STATIC: ${OC_STATIC}")
message(STATUS "OC_TESTS: ${OC_TESTS}")

# -Wno-unknown-pragmas needed due to libodb custom #pragma db
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -stdlib=libc++ -Wno-unknown-pragmas")
if(OC_DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -O0")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -g0")
endif(OC_DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")
message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

set(OC_INSTALL_DIR ${CMAKE_BINARY_DIR}/out)
set(OC_INSTALL_INCLUDE_DIR ${OC_INSTALL_DIR}/include)
set(OC_INSTALL_LIB_DIR ${OC_INSTALL_DIR}/lib)

include_directories(
  ./include/
  ${OC_INSTALL_INCLUDE_DIR}
)

link_directories(
  ${OC_INSTALL_LIB_DIR}
)

add_subdirectory(vendor/poco)
add_subdirectory(vendor/libodb)
add_subdirectory(vendor/libodb-sqlite)
add_subdirectory(src)

if(OC_TESTS)
  enable_testing()
  add_subdirectory(vendor/gtest)
  add_subdirectory(vendor/gmock)
  add_subdirectory(test)
endif()
