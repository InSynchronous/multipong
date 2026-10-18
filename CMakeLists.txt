cmake_minimum_required(VERSION 3.16)

project(multipong LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SHARED_SOURCES CONFIGURE_DEPENDS
  src/shared/*.cpp
)

file(GLOB_RECURSE CLIENT_SOURCES CONFIGURE_DEPENDS
  src/client/*.cpp
)

file(GLOB_RECURSE SERVER_SOURCES CONFIGURE_DEPENDS
  src/server/*.cpp
)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_ttf REQUIRED CONFIG)

add_executable(multipong
  ${SHARED_SOURCES}
  ${CLIENT_SOURCES}
)

target_link_libraries(multipong PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)

target_include_directories(multipong PRIVATE
  src
)

target_compile_options(multipong PRIVATE
  -O3
  -g
)

add_executable(multipong-server
  ${SERVER_SOURCES}
  ${SHARED_SOURCES}
)

target_include_directories(multipong-server PRIVATE
  src
)

target_compile_options(multipong-server PRIVATE
  -O3
  -g
)
