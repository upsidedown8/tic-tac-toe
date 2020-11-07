cmake_minimum_required(VERSION 3.0)
project(tic_tac_toe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

include_directories(
    src/
)

add_library(
    tic_tac_toe
    src/board.cpp
    src/game.cpp
)

add_executable(
    tic_tac_toe_console
    src/console_game.cpp
)
target_link_libraries(
    tic_tac_toe_console
    tic_tac_toe
)

find_package(PkgConfig REQUIRED)
set(SFML_USE_STATIC_STD_LIBS TRUE)

add_executable(
    tic_tac_toe_gui
    src/gui_game.cpp
)
target_link_libraries(
    tic_tac_toe_gui
    tic_tac_toe
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
)
