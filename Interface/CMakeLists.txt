cmake_minimum_required(VERSION 3.23)

project(Interface)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES Interface.cpp)
set(HEADERS Interface.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
