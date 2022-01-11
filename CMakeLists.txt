cmake_minimum_required(VERSION 2.8.3)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/teensy-arm.toolchain.cmake")

project(accessible_controller)

include(src)