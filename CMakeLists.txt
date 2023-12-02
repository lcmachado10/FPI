cmake_minimum_required(VERSION 2.8)
project( Open_CV_Project )
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( Open_CV_Project main.cpp
                
        operations.h
        operations.cpp
        cvui.h)
target_link_libraries( Open_CV_Project  ${OpenCV_LIBS})
include_directories(${CMAKE_SOURCE_DIR})
