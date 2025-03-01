#########################
# Example of CMakeLists #
#########################

cmake_minimum_required(VERSION 3.10)
project(mWeb CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mweb STATIC
  src/network.cpp
  src/http.cpp
  src/router.cpp
  src/core.cpp
)

target_include_directories(mweb PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

add_executable(example_server main.cpp)
target_link_libraries(example_server mweb)
