cmake_minimum_required(VERSION 3.23)

project(monopoly)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp)

add_subdirectory(Players)
add_subdirectory(Board)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})


target_link_libraries(${PROJECT_NAME} Players)
target_link_libraries(${PROJECT_NAME} Board)
