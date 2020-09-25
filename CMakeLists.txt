cmake_minimum_required(VERSION 3.0)

project(container_factory)

add_executable(container_factory main.cpp)

install(TARGETS container_factory RUNTIME DESTINATION bin)
