cmake_minimum_required(VERSION 3.23)

project(Board)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES Board.cpp)
set(HEADERS Board.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
