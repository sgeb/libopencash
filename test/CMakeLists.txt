set(GTEST_LIBS gtest gtest_main)
set(GMOCK_LIBS gmock gmock_main)
include_directories(
  ${GTEST_INCLUDE_DIRS}
)

link_directories(
  ${GTEST_LIBS_DIR}
)

#
# DocumentController
#

add_executable(TestDocumentController TestDocumentController.cpp)
target_link_libraries(TestDocumentController
  ${OC_LIB_NAME}
  ${GTEST_LIBS}
)
add_test(TestDocumentController TestDocumentController)
