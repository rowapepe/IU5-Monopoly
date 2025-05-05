cmake_minimum_required(VERSION 3.23)

project(Interface)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    Game.cpp
    Menu.cpp
    Slider.cpp
)

set(HEADERS
    Game.hpp
    Menu.hpp
    Slider.hpp
)

add_library(${PROJECT_NAME} STATIC
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
