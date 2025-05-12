find_package(spdlog REQUIRED)
find_package(dbg-macro REQUIRED)
find_package(Qt6 REQUIRED)

qt_standard_project_setup()
qt_add_executable(
  mainwindow
  main.cc
  mainwindow.hpp
  mainwindow.cc)

target_link_libraries(mainwindow PRIVATE c_cpp_learn::c_cpp_learn_options c_cpp_learn::c_cpp_learn_warnings)
target_link_system_libraries(
  mainwindow
  PRIVATE
  spdlog::spdlog
  dbg-macro::dbg-macro
  qt::qt)

target_include_directories(mainwindow PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
target_include_directories(mainwindow ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

set_target_properties(mainwindow PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE ON)
