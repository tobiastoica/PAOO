cmake_minimum_required(VERSION 3.2)
project(lucrare3_oop_fundamentals)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(inc)

set(myfiles 
    src/DynamicBuffer.cpp 
    src/ShallowBufferDemo.cpp 
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${myfiles})
