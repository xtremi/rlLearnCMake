cmake_minimum_required(VERSION 3.10)
project(hello_world)
add_executable(${PROJECT_NAME} helloworld.cpp)

add_subdirectory(useless)
target_include_directories(${PROJECT_NAME} PUBLIC useless)
target_link_libraries(${PROJECT_NAME} useless)