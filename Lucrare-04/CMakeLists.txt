cmake_minimum_required(VERSION 3.2)
project(lucrare4_effective_cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(inc)

set(myfiles 
    src/Item4_Initialization.cpp
    src/Item5_SilentlyGenerated.cpp
    src/Item6_DisallowFunctions.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${myfiles})
