cmake_minimum_required(VERSION 3.0.0)

project(sfml-app)

file(GLOB SRC "src/*.hpp" "src/*.cpp")

set(EXECUTABLE_OUTPUT_PATH CMAKE_SOURCE_DIR)

add_executable(CMAKE_PROJECT_NAME ${SRC})

target_link_libraries(CMAKE_PROJECT_NAME sfml-window sfml-graphics sfml-system)