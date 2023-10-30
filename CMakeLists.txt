cmake_minimum_required(VERSION 3.4...3.18)
project(city_course)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-std=gnu++17")

file(GLOB src_code
     "./src/*/*.cpp"
)

add_library(course_code STATIC ${src_code})
set_target_properties(course_code PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_subdirectory(pybind11)
pybind11_add_module(city_course pywrap.cpp)
target_link_libraries(city_course PRIVATE course_code)
