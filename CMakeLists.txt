cmake_minimum_required(VERSION 3.24)
project(enpitsu)

set(CMAKE_CXX_STANDARD 23)

if(EXISTS ${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/../conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(FATAL_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR}/../)

find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)

link_libraries(${CONAN_LIBS})
include_directories(${CONAN_INCLUDE_DIRS} include)

file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES src/*.cpp)

add_library(enpitsu STATIC ${HEADER_FILES} ${SOURCE_FILES})

# ====================below are configurations simply for testing the library======================

add_executable(test main.cpp)

target_link_directories(test PUBLIC src)

target_link_libraries(test ${CMAKE_BINARY_DIR}/lib/enpitsu.lib)



