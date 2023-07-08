cmake_minimum_required(VERSION 3.20.0)

project(anui_example)

add_executable(${PROJECT_NAME} hello_world)

target_link_libraries(anui)