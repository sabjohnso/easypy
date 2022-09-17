macro(easypy_add_test test_name)
  set(lib_name ${test_name}_test)
  set(source_name ${lib_name}.cpp)
  set(python_name test_${lib_name}.py)
  set(template_name ${python_name}.in)

  configure_file(${python_name}.in ${python_name})

  add_library(${lib_name} SHARED ${test_name}_test.cpp)
  target_link_libraries(${lib_name} PRIVATE easypy::header pybind11::headers Python3::Module pfr::header)
  set_target_properties(${lib_name}
    PROPERTIES
    CXX_STANDARD ${easypy_CXX_STANDARD}
    PREFIX "")

  add_test(
    NAME ${test_name}
    COMMAND pipenv run pytest ${CMAKE_CURRENT_BINARY_DIR}/${python_name}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endmacro()

easypy_add_test(introspective_binding)
target_link_libraries(introspective_binding_test PRIVATE introspection::header)
