cmake_minimum_required(VERSION 3.3)

# configure variables
set (LIB_NAME "HttpLib")

# configure directories
set (LIB_SRC_PATH "${PROJECT_SOURCE_DIR}/src")

# set sources
file (GLOB LIB_SOURCE_FILES "${LIB_SRC_PATH}/*.cpp")
file (GLOB LIB_HEADER_FILES "${LIB_SRC_PATH}/*.h")

# set library
add_library (${LIB_NAME} STATIC ${LIB_HEADER_FILES} ${LIB_SOURCE_FILES})

enable_testing ()
add_subdirectory (test)
