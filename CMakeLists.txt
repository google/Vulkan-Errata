# Copyright 2023 Google LLC
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.14)
project (vulkan_errata)

# Googletest requires C++14
set(CMAKE_CXX_STANDARD 14)

# Add dependency to gtest.  This code is taken from the googletest documentation.
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable (errata_tests
  src/vulkan-errata.h
  src/vulkan-errata.c
  src/vulkan-errata.hpp
  src/vulkan-errata.cpp
  tests/tests.cpp
  tests/cpp-compat.cpp)

target_link_libraries(
  errata_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(errata_tests)
