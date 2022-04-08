cmake_minimum_required(VERSION 3.15)
project(cpp-opencv-things)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(project main.cpp)
target_link_libraries(project ${OpenCV_LIBS})

add_compile_options(-Wall -Wextra -Werror -pedantic)
