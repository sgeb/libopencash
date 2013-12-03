cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(OC_LIB_NAME opencash)
set(OC_PROJECT_NAME "lib${OC_LIB_NAME}")

option(OC_DEBUG "Build a debug version of ${OC_PROJECT_NAME} and its dependencies (default: build a release version)." OFF)
option(OC_STATIC "Build a static version of ${OC_PROJECT_NAME} and its dependencies (default: enabled)." ON)
option(OC_TESTS "Build all of ${OC_PROJECT_NAME}'s unit tests (default: OFF)." OFF)
set(OC_PLATFORM "host" CACHE STRING "Build ${OC_PROJECT_NAME} for a particular platform. Options are 'host', 'ios-device' or 'ios-simulator' (default: host).")

if(OC_DEBUG)
  set(CMAKE_BUILD_TYPE "Debug")
else()
  set(CMAKE_BUILD_TYPE "Release")
endif(OC_DEBUG)

if(OC_PLATFORM STREQUAL "host")
  set(OC_PLATFORM_HOST ON)
elseif(OC_PLATFORM STREQUAL "ios-device")
  set(OC_PLATFORM_IOS_DEVICE ON)
elseif(OC_PLATFORM STREQUAL "ios-simulator")
  set(OC_PLATFORM_IOS_SIMULATOR ON)
else()
  message(FATAL_ERROR "OC_PLATFORM set to invalid value: '${OC_PLATFORM}'")
endif()

if(OC_PLATFORM_IOS_DEVICE OR OC_PLATFORM_IOS_SIMULATOR)
  if(NOT OC_STATIC)
    set(OC_STATIC ON)
    message(WARNING "Setting OC_STATIC to ON for OC_PLATFORM '${OC_PLATFORM}'")
  endif()
  if(OC_TESTS)
    set(OC_TESTS OFF)
    message(WARNING "Setting OC_TESTS to OFF for OC_PLATFORM '${OC_PLATFORM}'")
  endif()
endif()

if(OC_STATIC)
  set(BUILD_SHARED_LIBS OFF)
else()
  set(BUILD_SHARED_LIBS ON)
endif(OC_STATIC)

if(OC_PLATFORM_IOS_DEVICE OR OC_PLATFORM_IOS_SIMULATOR)
  if(OC_PLATFORM_IOS_DEVICE)
    set(IOS_PLATFORM "OS")
  else()
    set(IOS_PLATFORM "SIMULATOR")
  endif()
  # Must be included before project declaration
  include(ios-toolchain)
endif()

# Project must be declared before adjustments to CMAKE_CXX_FLAGS
project(${OC_PROJECT_NAME} CXX)

# -Wno-unknown-pragmas needed due to libodb custom #pragma db
set(OC_CXX_ADDITIONAL_FLAGS "-Wall -std=c++11 -stdlib=libc++ -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OC_CXX_ADDITIONAL_FLAGS}")
if(OC_DEBUG)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -g0")
endif(OC_DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(OC_INSTALL_DIR ${CMAKE_BINARY_DIR}/out)
set(OC_INSTALL_INCLUDE_DIR ${OC_INSTALL_DIR}/include)
set(OC_INSTALL_LIB_DIR ${OC_INSTALL_DIR}/lib)

message(STATUS "OC_DEBUG: ${OC_DEBUG}")
message(STATUS "OC_STATIC: ${OC_STATIC}")
message(STATUS "OC_TESTS: ${OC_TESTS}")
message(STATUS "OC_PLATFORM: ${OC_PLATFORM}")
#message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

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
