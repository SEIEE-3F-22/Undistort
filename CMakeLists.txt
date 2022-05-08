cmake_minimum_required(VERSION 3.16)
project(Undistort)

set(CMAKE_CXX_STANDARD 14)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
message(Library will be generated under ${LIBRARY_OUTPUT_PATH})

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/extern/pybind11/include)
add_subdirectory(extern/pybind11)

pybind11_add_module(Undistort Undistort.cpp)
target_link_libraries(Undistort PRIVATE ${OpenCV_LIBS})