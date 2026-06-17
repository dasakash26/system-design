cmake_minimum_required(VERSION 3.16)
project(NotificationSystemApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(NotificationSystemApp ${SRC_FILES})
