cmake_minimum_required(VERSION 3.0)
project(tic_tac_toe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

include_directories(
    src/
    inc/
)

set(
    SRC_FILES
    src/board.cpp
    src/game.cpp
)

find_package(PkgConfig REQUIRED)
find_package(Qt5 REQUIRED Core Widgets)

add_executable(
    tic_tac_toe_exec
    ${SRC_FILES}
    src/main.cpp
)
target_link_libraries(
    tic_tac_toe_exec
    Qt5::Widgets
)

# set(TARGET_NAME QtDemo)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
