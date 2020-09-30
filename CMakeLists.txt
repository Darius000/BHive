cmake_minimum_required(VERSION 3.17.2)

project(BHive)

include(scripts/utils.cmake)

add_executable(Glad)
add_executable(GLFW)
add_executable(ImGui)
add_executable(BHive)
add_executable(BHiveEditor)
add_executable(Sandbox)

target_parse_sources(BHive)