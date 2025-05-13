include(GenerateExportHeader)

add_library(calculator calculator.cpp)
add_library(c_cpp_learn::calculator ALIAS calculator)
target_link_libraries(calculator PRIVATE c_cpp_learn_options c_cpp_learn_warnings)

target_include_directories(calculator ${WARNING_GUARD} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                                              $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)

target_compile_features(calculator PUBLIC cxx_std_20)
set_target_properties(
  calculator
  PROPERTIES VERSION ${PROJECT_VERSION}
             CXX_VISIBILITY_PRESET hidden
             VISIBILITY_INLINES_HIDDEN YES)
generate_export_header(calculator EXPORT_FILE_NAME
${PROJECT_BINARY_DIR}/include/c_cpp_learn/calculator_export.hpp)
if(NOT BUILD_SHARED_LIBS)
  target_compile_definitions(calculator PUBLIC SAMPLE_LIBRARY_STATIC_DEFINE)
endif()
