cmake_minimum_required(VERSION 3.10)
project(TombOfTheMask_CPP)

set(CMAKE_CXX_STANDARD 17)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(TombGame main.cpp)

target_link_libraries(TombGame sfml-graphics sfml-window sfml-system)