cmake_minimum_required(VERSION 3.23)

project(monopoly)

add_subdirectory(Board)
add_subdirectory(Interface)
add_subdirectory(Players)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(monopoly main.cpp)

target_link_libraries(monopoly PRIVATE
    Interface
    Players
    Board

    sfml-graphics
    sfml-window
    sfml-audio
    sfml-system
)
