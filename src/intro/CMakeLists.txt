add_executable(intro main.cc stack.hpp calc.hpp)

find_package(spdlog REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(dbg-macro REQUIRED)
find_package(CLI11 REQUIRED)

target_link_libraries(intro PRIVATE c_cpp_learn::c_cpp_learn_options c_cpp_learn::c_cpp_learn_warnings)
target_link_system_libraries(
  intro
  PRIVATE
  spdlog::spdlog
  JsonCpp::JsonCpp
  dbg-macro::dbg-macro
  CLI11::CLI11)

target_include_directories(intro PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")
