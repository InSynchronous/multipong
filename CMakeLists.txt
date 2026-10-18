cmake_minimum_required(VERSION 3.16)

project(multipong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  src/*.cpp
)

find_package(SDL3 REQUIRED CONFIG)

add_executable(multipong ${SOURCES})

target_link_libraries(multipong PRIVATE SDL3::SDL3)

target_include_directories(multipong PRIVATE
  src
)

target_compile_options(multipong PRIVATE
  -O3
)
