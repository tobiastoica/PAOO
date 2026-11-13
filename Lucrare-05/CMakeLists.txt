cmake_minimum_required(VERSION 3.2)
project(lucrare5_effective_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(inc)

set(myfiles 
    src/Item10_AssignmentReturnThis.cpp
    src/Item11_SelfAssignment.cpp
    src/Item12_CopyAllParts.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${myfiles})
