cmake_minimum_required(VERSION 3.2)
project(lucrare1_env_check)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(myfiles src/main.cpp)
add_executable(${PROJECT_NAME} ${myfiles})
