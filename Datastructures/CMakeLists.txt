cmake_minimum_required(VERSION 3.16)
   
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(LowLevel LANGUAGES CXX)
 
 
if(NOT CYGWIN AND NOT MSYS AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL QNX)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_library(memalloc_lib STATIC mem_allocate.cpp)

target_include_directories(memalloc_lib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR} # so consumers can include "mem_allocate.hpp"
)

add_subdirectory(test)
