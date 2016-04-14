cmake_minimum_required(VERSION 3.0)
project(OpenChemicalGraphLibrary)

set(OpenChemicalGraphLibrary_VERSION 0.1.0)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# utility functions (e.g. copy_headers, add_gtest)
include(Functions)

############################################################
#
# C++ Compiler
#
############################################################

# headers will be copied here
include_directories(${CMAKE_BINARY_DIR}/include)

set(IGNORE_WARNINGS
  sign-compare
#  "gnu-zero-variadic-macro-arguments"
)

foreach(WARNING_NAME ${IGNORE_WARNINGS})
  set(IGNORE_WARNINGS_FLAGS "${IRGNORE_WARNINGS_FLAGS} -Wno-${WARNING_NAME}")
endforeach()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wextra ${IGNORE_WARNINGS_FLAGS}")

find_package(Threads)

############################################################
#
# Doxygen Documentation
#
############################################################

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )
endif()

############################################################
#
# Library
#
############################################################

add_subdirectory(src)

############################################################
#
# Tests
#
############################################################

option(BUILD_TESTS "Build unittests (requires google test library)" OFF)
if(${BUILD_TESTS})
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
  enable_testing()
  add_subdirectory(test)
endif()

############################################################
#
# Benchmarks
#
############################################################

option(BUILD_BENCHMARKS "Build benchmarks (requires google benchmark library)" OFF)
if(${BUILD_BENCHMARKS})
  add_subdirectory(benchmark)
endif()

############################################################
#
# Examples
#
############################################################

option(BUILD_EXAMPLES "Build examples" ON)
if(${BUILD_EXAMPLES})
  add_subdirectory(examples)
endif()

############################################################
#
# CMake configuratio file
#
############################################################

configure_file(
  "${CMAKE_SOURCE_DIR}/cmake/OpenChemicalGraphLibraryConfig.cmake.in"
  "${CMAKE_BINARY_DIR}/OpenChemicalGraphLibraryConfig.cmake"
  @ONLY
)

configure_file(
  "${CMAKE_SOURCE_DIR}/cmake/OpenChemicalGraphLibraryConfigVersion.cmake.in"
  "${CMAKE_BINARY_DIR}/OpenChemicalGraphLibraryConfigVersion.cmake"
  @ONLY
)

install(FILES
  "${CMAKE_BINARY_DIR}/OpenChemicalGraphLibraryConfig.cmake"
  "${CMAKE_BINARY_DIR}/OpenChemicalGraphLibraryConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/OpenChemicalGraphLibrary"
)
