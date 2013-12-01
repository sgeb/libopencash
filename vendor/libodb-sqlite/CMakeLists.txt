cmake_minimum_required(VERSION 2.8.8)
project(libodb-sqlite_builder C CXX)
include(ExternalProject)

if(OC_STATIC)
  set(CONFIGURE_ARGS --enable-static --disable-shared)
else()
  set(CONFIGURE_ARGS --enable-shared --disable-static)
endif()

if(OC_TARGET_IOS)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=armv7 --build=x86_64 --disable-threads)
elseif(OC_TARGET_IOSSIMULATOR)
  set(CONFIGURE_ARGS ${CONFIGURE_ARGS} --host=i386 --build=x86_64 --disable-threads)
endif()

ExternalProject_Add(libodb-sqlite
  URL http://www.codesynthesis.com/download/odb/2.3/libodb-sqlite-2.3.0.tar.gz
  URL_HASH SHA1=2643d3c2c3f273f3fb223759e4ad10635cc91ce8
  SOURCE_DIR ${PROJECT_BINARY_DIR}/src/libodb-sqlite

  PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
  INSTALL_DIR ${OC_INSTALL_DIR}
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  BUILD_IN_SOURCE 1

  CONFIGURE_COMMAND <SOURCE_DIR>/configure
    --prefix=<INSTALL_DIR> CXXFLAGS=${CMAKE_CXX_FLAGS}
    LDFLAGS=-L${OC_INSTALL_LIB_DIR} CPPFLAGS=-I${OC_INSTALL_INCLUDE_DIR}
    ${CONFIGURE_ARGS}

  BUILD_COMMAND make -j4 all

  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)
