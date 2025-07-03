cmake_minimum_required(VERSION 3.10)
project(WebServer C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add source files
include_directories(src/log)
file(GLOB SOURCES src/*.c)

add_executable(webserver ${SOURCES})

# Optionally include directories
target_include_directories(webserver PRIVATE include)