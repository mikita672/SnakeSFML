cmake_minimum_required(VERSION 3.22)
project(SnakeSFML)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5.1 COMPONENTS graphics)

add_executable(SnakeSFML main.cpp)

target_link_libraries(SnakeSFML sfml-graphics)

