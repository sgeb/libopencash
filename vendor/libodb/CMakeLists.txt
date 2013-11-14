cmake_minimum_required(VERSION 2.8.8)
project(libodb_builder C CXX)
include(ExternalProject)

if(OC_STATIC)
  set(CONFIGURE_ARGS_STATIC_SHARED --enable-static --disable-shared)
else()
  set(CONFIGURE_ARGS_STATIC_SHARED --enable-shared --disable-static)
endif()

ExternalProject_Add(libodb
  URL http://www.codesynthesis.com/download/odb/2.3/libodb-2.3.0.tar.gz
  URL_HASH SHA1=8ac9a09a6a86e73951289ee79c022661caea7f96
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/libodb

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}

  CONFIGURE_COMMAND <SOURCE_DIR>/configure
    --prefix=<INSTALL_DIR>
    ${CONFIGURE_ARGS_STATIC_SHARED}
    # ugly CXX hack to get CXX to use -stdlib=libc++ during linking
    CXX=${CMAKE_CXX_COMPILER}\ ${CMAKE_CXX_FLAGS}
    CXXFLAGS=${CMAKE_CXX_FLAGS}

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)
