cmake_minimum_required(VERSION 3.0)

project(Font)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable(cnfont cnfont.cpp)
target_link_libraries(cnfont ${VTK_LIBRARIES})