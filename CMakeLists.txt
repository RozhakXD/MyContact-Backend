cmake_minimum_required(VERSION 3.10)

project(MyContactBackend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(SQLite3 REQUIRED)

find_path(ASIO_INCLUDE_DIR asio.hpp)
if(NOT ASIO_INCLUDE_DIR)
    message(FATAL_ERROR "ASIO not found. Please install libasio-dev")
endif()

include_directories(${CMAKE_SOURCE_DIR}/third_party)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${ASIO_INCLUDE_DIR})

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(MyContact ${SOURCES})

target_link_libraries(MyContact 
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
    sqlite3
)

target_compile_definitions(MyContact PRIVATE ASIO_STANDALONE)