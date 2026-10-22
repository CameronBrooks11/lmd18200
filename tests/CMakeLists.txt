cmake_minimum_required(VERSION 3.16)
project(LMD18200Tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(lmd18200 STATIC
  ../src/LMD18200.cpp
  fakes/Arduino.cpp)
target_include_directories(lmd18200 PUBLIC ../src fakes)
target_compile_options(lmd18200 PRIVATE -Wall -Wextra)

enable_testing()
foreach(name test_read_current test_release_order test_smoke)
  add_executable(${name} ${name}.cpp)
  target_link_libraries(${name} PRIVATE lmd18200)
  add_test(NAME ${name} COMMAND ${name})
endforeach()
