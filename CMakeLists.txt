cmake_minimum_required(VERSION 3.1)

project(FastRotate90)

set (CMAKE_CXX_STANDARD 11)

find_package( OpenCV REQUIRED )
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )
