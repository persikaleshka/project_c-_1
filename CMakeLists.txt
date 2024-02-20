cmake_minimum_required(VERSION 3.0)
project(project_c-_1)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(BigNumber)
add_executable(main main.cpp)
target_link_libraries(main BigNumber)