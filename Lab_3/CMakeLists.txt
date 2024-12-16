cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-g -rdynamic)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

add_executable(tests test/tests01.cpp)
target_link_libraries(tests ${CMAKE_PROJECT_NAME}_lib gtest_main)

add_test(NAME MyProjectTests COMMAND tests)