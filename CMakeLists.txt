add_library(
  hoops STATIC
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

add_executable(test_source src/test/hoops_lim_test.cxx)
add_executable(test_hoops src/test/hoops_lim_test.cxx)

target_link_libraries(test_source PRIVATE hoops)
target_link_libraries(test_hoops PRIVATE hoops)
