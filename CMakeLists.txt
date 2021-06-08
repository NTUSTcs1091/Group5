cmake_minimum_required(VERSION 3.3)

project (Group5)

# set default variable
option(Boost_USE_STATIC_LIBS "Use static library." ON)
option(Boost_USE_MULTITHREAD "Use multithread" ON)
option(Boost_USE_STATIC_RUNTIME "Use static runtime" ON)
option(Boost_USE_DEBUG_RUNTIME "Use debug runtime" ON)

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
