cmake_minimum_required(VERSION 2.8.8)
project(poco_builder C CXX)
include(ExternalProject)

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

macro(ExternalProject_Add_poco PNAME PCONFIG_ARGS PINSTALL_DIR)
  ExternalProject_Add(${PNAME}
    URL https://github.com/pocoproject/poco/archive/poco-1.5.2-release.tar.gz
    URL_MD5 4ed751311fe4eb437a485139fcfdf558
    SOURCE_DIR ${PROJECT_BINARY_DIR}/src/${PNAME}

    PREFIX "${CMAKE_CURRENT_BINARY_DIR}"
    INSTALL_DIR ${PINSTALL_DIR}
    UPDATE_COMMAND ""
    BUILD_IN_SOURCE 1

    # Unfortunately the poco Makefile isn't as flexible as we'd like, so we copy
    # our own Makefile extensions to the source dir
    PATCH_COMMAND ${CMAKE_COMMAND} -E copy
      "${CMAKE_CURRENT_SOURCE_DIR}/Makefile-custom" <SOURCE_DIR>/Makefile-custom

    CONFIGURE_COMMAND <SOURCE_DIR>/configure --no-tests --no-samples
      --prefix=<INSTALL_DIR> ${PCONFIG_ARGS}

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
endmacro()

if(OC_TARGET_IOS)

  ExternalProject_Add_poco(poco-ios
    --config=iPhone-clang
    ${PROJECT_BINARY_DIR}/out/poco-ios
  )

  ExternalProject_Add_poco(poco-iossimulator
    --config=iPhoneSimulator-clang
    ${PROJECT_BINARY_DIR}/out/poco-iossimulator
  )

  add_custom_target(poco-universal
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OC_INSTALL_LIB_DIR}
    COMMAND lipo -create
      ${PROJECT_BINARY_DIR}/out/poco-ios/lib/libPocoFoundation.a
      ${PROJECT_BINARY_DIR}/out/poco-iossimulator/lib/libPocoFoundation.a
      -output ${OC_INSTALL_LIB_DIR}/libPocoFoundation.a
    COMMENT "Creating universal library (ios, iossimulator)"
    VERBATIM
  )

  add_custom_target(poco-copy-public-headers
    COMMAND ${CMAKE_COMMAND} -E make_directory ${OC_INSTALL_INCLUDE_DIR}/Poco
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${PROJECT_BINARY_DIR}/out/poco-ios/include/Poco
      ${OC_INSTALL_INCLUDE_DIR}/Poco
    COMMENT "Copying public headers for POCO"
    VERBATIM
  )
  add_dependencies(poco-copy-public-headers poco-ios)

  add_custom_target(poco)
  add_dependencies(poco
    poco-ios poco-iossimulator poco-universal poco-copy-public-headers
  )

else()
  ExternalProject_Add_poco(poco "" ${OC_INSTALL_DIR})
endif()
