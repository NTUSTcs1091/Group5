cmake_minimum_required(VERSION 3.3)

project (Group5)

# set default variable
option(Boost_USE_STATIC_LIBS "Use static library." ON)
option(Boost_USE_MULTITHREAD "Use multithread" ON)
option(Boost_USE_STATIC_RUNTIME "Use static runtime" ON)
option(Boost_USE_DEBUG_RUNTIME "Use debug runtime" ON)

# find boost library
find_package(Boost REQUIRED date_time)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIR})
ENDIF(Boost_FOUND)

# find openssl library
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
    # for using thread
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY 1)
    set(CMAKE_USE_WIN32_THREADS_INIT 0)
    set(CMAKE_USE_PTHREADS_INIT 1)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -Wall -Wextra -Wpedantic -Wno-unused-parameter")
endif()

enable_testing ()
add_subdirectory (src)
