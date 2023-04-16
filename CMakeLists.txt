cmake_minimum_required(VERSION 3.20)

project(sauer_cheetos)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNICODE -D_UNICODE")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DUNICODE -D_UNICODE")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB MAIN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(muniyaniyo SHARED ${MAIN_SOURCES})
