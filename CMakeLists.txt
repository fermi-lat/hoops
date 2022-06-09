add_library(
  hoops 
  src/hoops_ape.cxx
  src/hoops_exception.cxx
  src/hoops_group.cxx
  src/hoops_limits.cxx
  src/hoops_par.cxx
  src/hoops_prim.cxx
  src/hoops_prompt_group.cxx
)

target_include_directories(
  hoops PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>
)

target_link_libraries(hoops PRIVATE ape)

add_executable(test_hoops src/test/hoops_lim_test.cxx)
target_link_libraries(test_hoops PRIVATE hoops)

target_compile_definitions(test_hoops PRIVATE HAVE_LIMITS)

###############################################################
# Installation
###############################################################
install(DIRECTORY hoops DESTINATION ${FERMI_INSTALL_INCLUDEDIR})
install(DIRECTORY data/ DESTINATION ${FERMI_INSTALL_DATADIR})

install(
  TARGETS hoops test_hoops
  EXPORT fermiTargets
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
