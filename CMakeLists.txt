cmake_minimum_required(VERSION 3.9)

project(InlineResources)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

include(CMake/InlineResources/InlineResourcesConfig.cmake)

install(DIRECTORY CMake/InlineResources DESTINATION lib/cmake)

add_subdirectory(Lib)
