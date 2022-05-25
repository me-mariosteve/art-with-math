cmake_minimum_required(VERSION 3.15)
project(cpp-opencv-things)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(project src/main.cpp)
target_link_libraries(project ${OpenCV_LIBS})

target_include_directories(project
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/includes/includes.hpp
        PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -O5")
