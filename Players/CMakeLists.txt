cmake_minimum_required(VERSION 3.23)

project(Players)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Dice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/Dice.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/GameLogic.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Player.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
