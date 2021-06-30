cmake_minimum_required(VERSION 3.3)

# configure variables
set (TEST_NAME "TEST_LIB")

#configure directories
set (TEST_MODULE_PATH "${LIB_SRC_PATH}/test")

#configure test directories
set (TEST_SRC_PATH  "${TEST_MODULE_PATH}/src" )

#set includes
include_directories (${LIB_SRC_PATH})

# include(GoogleTest)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#set test sources
file (GLOB TEST_SOURCE_FILES "${TEST_SRC_PATH}/*.cpp")

#set target executable
add_executable (${TEST_NAME} ${TEST_SOURCE_FILES})

target_link_libraries (${TEST_NAME} ${LIB_NAME} ${Boost_LIBRARIES} ${GTEST_MAIN_LIBRARY} ${GTEST_LIBRARIES} pthread)

enable_testing()
gtest_discover_tests(${TEST_NAME})
add_test(MyTest ${TEST_NAME})
