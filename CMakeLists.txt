cmake_minimum_required(VERSION 3.24)
project(enpitsu)

set(CMAKE_CXX_STANDARD 23)

if(EXISTS ${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/../)

add_library(enpitsu STATIC
        src/Screen.h
        src/Screen.cpp)

add_executable(test main.cpp)

target_include_directories(test PUBLIC headers)
target_link_directories(test PUBLIC src)

target_link_libraries(test ${CMAKE_BINARY_DIR}/lib/enpitsu.lib)

link_libraries(${CONAN_LIBS})

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(GLEW REQUIRED)

