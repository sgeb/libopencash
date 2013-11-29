cmake_minimum_required(VERSION 2.8.8)
project(poco_builder C CXX)
include(ExternalProject)

if(OC_TARGET_IOS)
  set(CONFIGURE_ARGS --config=iPhone-clang)
endif()

if(OC_STATIC)
  set(BUILD_TARGET my_static)
else()
  set(BUILD_TARGET my_shared)
endif()

if(OC_DEBUG)
  set(BUILD_TARGET ${BUILD_TARGET}_debug)
else()
  set(BUILD_TARGET ${BUILD_TARGET}_release)
endif()

ExternalProject_Add(poco
  URL https://github.com/pocoproject/poco/archive/poco-1.5.2-release.tar.gz
  URL_MD5 4ed751311fe4eb437a485139fcfdf558
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/poco

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}
  UPDATE_COMMAND ""
  BUILD_IN_SOURCE 1

  # Unfortunately the poco Makefile isn't as flexible as we'd like, so we copy
  # our own Makefile extensions to the source dir
  PATCH_COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_SOURCE_DIR}/Makefile-custom" <SOURCE_DIR>/Makefile-custom

  CONFIGURE_COMMAND ./configure ${CONFIGURE_ARGS}
    --no-tests --no-samples --prefix=${OC_INSTALL_DIR} --cflags="${CXX_FLAGS}"

  # Source our custom Makefile before building
  BUILD_COMMAND make -f Makefile -f Makefile-custom -j4 ${BUILD_TARGET}

  # Source our custom Makefile before installing
  INSTALL_COMMAND make -f Makefile -f Makefile-custom my_install

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)
