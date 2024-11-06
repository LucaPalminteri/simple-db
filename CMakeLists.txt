cmake_minimum_required(VERSION 3.10)
project(SimpleDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(simpledb
    src/main.cpp
    src/network/server.cpp
)

target_include_directories(simpledb PRIVATE src)
target_link_libraries(simpledb pthread)
