cmake_minimum_required(VERSION 3.5)

set(CXX_DISABLE_WERROR 1)
set(CMAKE_CXX_STANDARD 11)

set(PROJECT_NAME mc_ur5e)
set(PROJECT_DESCRIPTION "UR5e robot module for mc_rtc")

project(${PROJECT_NAME} LANGUAGES CXX VERSION 1.0.0)
include(CTest)
enable_testing()

find_package(mc_rtc REQUIRED)

add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
