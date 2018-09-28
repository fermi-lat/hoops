cmake_minimum_required(VERSION 3.11)
include(GNUInstallDirs)
include(FetchContent)

project(hoops
  VERSION 0.0.0
  LANGUAGES CXX
  )

###############################################################################
#
# External dependencies managed through fetchcontent
#
###############################################################################

fetchcontent_declare(ape
  GIT_REPOSITORY https://github.com/fermi-lat/ape.git
  GIT_TAG standalone
  )

fetchcontent_getproperties(ape)
if(NOT ape_POPULATED)
  fetchcontent_populate(ape)
  add_subdirectory(${ape_SOURCE_DIR} ${ape_BINARY_DIR})
endif()

###############################################################################


###############################################################################
#
# Hoops targets
#
###############################################################################

add_library(hoops STATIC
  src/hoops_ape.cxx
  src/hoops_exception.cxx
  src/hoops_group.cxx
  src/hoops_limits.cxx
  src/hoops_par.cxx
  src/hoops_prim.cxx
  src/hoops_prompt_group.cxx
)
add_library(ST::hoops ALIAS hoops)
target_include_directories(hoops
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
target_link_libraries(hoops PRIVATE ST::ape)


set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/hoops)

install(DIRECTORY hoops DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS hoops
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

install(TARGETS hoops
  EXPORT hoopsTargets
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )

install(EXPORT hoopsTargets
  NAMESPACE    ST::
  DESTINATION  ${INSTALL_CONFIGDIR}
  )

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/hoopsConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/hoopsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/hoopsConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/hoopsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/hoopsConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

export(EXPORT hoopsTargets
  FILE ${CMAKE_CURRENT_BINARY_DIR}/hoopsTargets.cmake
  NAMESPACE ST::
)

#Register package in user's package registry
export(PACKAGE hoops)
