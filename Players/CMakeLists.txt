cmake_minimum_required(VERSION 3.23)

project(Players)

set(SOURCES
    Player.cpp
    Dice.cpp
)

set(HEADERS
    Player.hpp
    Dice.hpp
)

add_library(${PROJECT_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
