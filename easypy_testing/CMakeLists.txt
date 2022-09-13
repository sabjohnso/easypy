find_package(GTest)

macro(easypy_add_test test_name exe_name)
  add_executable(${exe_name} ${ARGN})
  target_link_libraries(${exe_name} PRIVATE
    easypy::header
    GTest::gtest_main)
  set_target_properties(${exe_name}
    PROPERTIES
    CXX_STANDARD ${easypy_CXX_STANDARD})
  add_test(${test_name} ${exe_name})
endmacro()
