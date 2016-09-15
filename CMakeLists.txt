cmake_minimum_required (VERSION 2.6)
project (flyweight)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMAND ON)
enable_testing()
add_subdirectory(test)
add_library(libflyweight INTERFACE)
target_include_directories(libflyweight INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR})
