cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(c_cpp_learn CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET c_cpp_learn_options)
    message(FATAL_ERROR "Required config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE c_cpp_learn::c_cpp_learn_options c_cpp_learn::c_cpp_learn_warnings gtest::gtest)

if(NOT CMAKE_CROSSCOMPILING)
  # Only when not cross-compiling, we can use gtest_discover_tests
  # to automatically discover and register tests to ctest.
  gtest_discover_tests(tests)
endif()
