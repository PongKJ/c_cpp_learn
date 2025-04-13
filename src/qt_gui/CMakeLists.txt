find_package(spdlog REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(dbg-macro REQUIRED)
find_package(CLI11 REQUIRED)
find_package(Qt6 REQUIRED)

qt_standard_project_setup()
qt_add_executable(
  qt_gui
  main.cc
  ui/mainwindow.ui
  mainwindow.hpp
  mainwindow.cc)

target_link_libraries(qt_gui PRIVATE c_cpp_learn::c_cpp_learn_options c_cpp_learn::c_cpp_learn_warnings)
target_link_system_libraries(
  qt_gui
  PRIVATE
  spdlog::spdlog
  JsonCpp::JsonCpp
  dbg-macro::dbg-macro
  CLI11::CLI11
  qt::qt)

target_include_directories(qt_gui PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
target_include_directories(qt_gui ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

set_target_properties(qt_gui PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE ON)
