cmake_minimum_required(VERSION 2.8.8)
project(poco_builder C CXX)
include(ExternalProject)

ExternalProject_Add(poco
  URL https://github.com/pocoproject/poco/archive/poco-1.5.2-release.tar.gz
  URL_MD5 4ed751311fe4eb437a485139fcfdf558
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/poco

  CMAKE_ARGS
      -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
      -DPOCO_STATIC=${OC_STATIC}
      -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
      -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
      -DCMAKE_CXX_FLAGS_DEBUG=${CMAKE_CXX_FLAGS_DEBUG}
      -DCMAKE_CXX_FLAGS_RELEASE=${CMAKE_CXX_FLAGS_RELEASE}
  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}

  # Overwrite CMakeLists.txt with custom one
  # so that we only build required libraries
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists-poco.txt" <SOURCE_DIR>/CMakeLists.txt

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)
