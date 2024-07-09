cmake_minimum_required(VERSION 3.14)

project(hpcgraAssembler)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories("${CMAKE_SOURCE_DIR}/include")
file(GLOB_RECURSE CPP_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${CPP_SRCS})
