cmake_minimum_required (VERSION 3.11)
set (CMAKE_CXX_STANDARD 11)
project (PixelSortSDL2)

find_package(SDL2 REQUIRED)

add_executable(PixelSort main.cpp)

target_link_libraries(PixelSort ${SDL2_LIBRARIES})    
