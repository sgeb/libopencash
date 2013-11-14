cmake_minimum_required(VERSION 2.8.8)
project(gtest_builder C CXX)
include(ExternalProject)

ExternalProject_Add(googletest
  URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
  URL_MD5 2d6ec8ccdf5c46b05ba54a9fd1d130d7
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/googletest

  CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -Dgtest_force_shared_crt=ON
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
      -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"

  # Disable install step
  INSTALL_COMMAND ""

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  #LOG_CONFIGURE ON
  #LOG_BUILD ON
)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${source_dir}/include PARENT_SCOPE)

# Specify link libraries
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBS_DIR ${binary_dir} PARENT_SCOPE)
