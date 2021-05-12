cmake_minimum_required(VERSION 3.3)

project (Group5)

# set default variable
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREAD ON)
SET(Boost_USE_STATIC_RUNTIME ON)
SET(Boost_USE_DEBUG_RUNTIME ON)

# find boost library     date_time 
find_package(Boost REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIR})
ENDIF(Boost_FOUND)

find_package(OpenSSL)
if (OPENSSL_FOUND)
    link_libraries(${OPENSSL_LIBRARIES})
    include_directories (${OPENSSL_INCLUDE_DIR})
endif()

if (MSVC)
    # set run-time mode
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic -Wno-unused-parameter")
endif()

add_subdirectory (src)
