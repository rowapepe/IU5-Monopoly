cmake_minimum_required(VERSION 3.23)

project(Board)

set(SOURCES
    Board.cpp
    Cells.cpp
    Cards.cpp
)

set(HEADERS
    Board.hpp
    Cells.hpp
    Cards.hpp
)

add_library(${PROJECT_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
