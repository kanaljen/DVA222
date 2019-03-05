cmake_minimum_required(VERSION 3.1)

project(Project)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
add_executable(Project Main.cpp Engine.cpp Engine.hpp Gamemenu.cpp GameObjects.cpp GameObjects.hpp Gameplay.cpp Gamestate.cpp Snake.cpp Snake.hpp Topmenu.cpp States.hpp)
target_link_libraries(Project sfml-graphics sfml-audio)