cmake_minimum_required(VERSION 3.28)
project(DaSiamRPN_tracker_cpp)

set(OpenCV_DIR /home/pardusumsu/code/opencv-4.10.0/build)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(DaSiamRPN_tracker_cpp main.cpp
        tracker.cpp
        tracker.h)

target_link_libraries(DaSiamRPN_tracker_cpp ${OpenCV_LIBS})
