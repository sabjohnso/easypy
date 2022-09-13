configure_file(config.hpp.in config.hpp)

add_library(easypy_header INTERFACE)
set_target_properties(easypy_header PROPERTIES EXPORT_NAME header)
target_include_directories(easypy_header
  INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
  $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
  $<INSTALL_INTERFACE:${easypy_INSTALL_INCLUDEDIR}>)

add_library(easypy::header ALIAS easypy_header)
  
install(TARGETS easypy_header
  EXPORT easypy_EXPORTS
  RUNTIME DESTINATION ${easypy_INSTALL_BINDIR}
  LIBRARY DESTINATION ${easypy_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${easypy_INSTALL_LIBDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/config.hpp
  DESTINATION ${easypy_INSTALL_INCLUDEDIR}/easypy)
