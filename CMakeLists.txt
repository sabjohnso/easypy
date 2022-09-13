cmake_minimum_required(VERSION 3.12)

project(easypy VERSION 0.1.0 LANGUAGES C CXX)

option(easypy_BUILD_TESTING "Build the easypy tests" ON)
set(easypy_CXX_STANDARD 20 CACHE STRING "C++ standard for easypy")

include(GNUInstallDirs)
set(easypy_INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR})
set(easypy_INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR})
set(easypy_INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
set(easypy_INSTALL_CONFDIR ${easypy_INSTALL_LIBDIR}/cmake/easypy-${PROJECT_VERSION})

list(INSERT CMAKE_MODULE_PATH 0 ${PROJECT_SOURCE_DIR}/cmake)
include(easypy_deps)

add_subdirectory(easypy)

if(easypy_BUILD_TESTING)
  include(CTest)
  if(BUILD_TESTING)
    add_subdirectory(easypy_testing)
  endif()
endif()

install(EXPORT easypy_EXPORTS
  NAMESPACE easypy::
  FILE easypy-exports.cmake
  DESTINATION ${easypy_INSTALL_CONFDIR})

configure_file(easypy-config.cmake.in easypy-config.cmake)
install(FILES ${PROJECT_BINARY_DIR}/easypy-config.cmake
  DESTINATION ${easypy_INSTALL_CONFDIR})
