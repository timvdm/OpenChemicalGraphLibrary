project(OpenChemicalGraphLibrary)
cmake_minimum_required(VERSION 3.0)

# utility functions (e.g. copy_headers, add_gtest)
include(Functions.cmake)

############################################################
#
# C++ Compiler
#
############################################################

# headers will be copied here
include_directories(${CMAKE_BINARY_DIR}/include)

set(IGNORE_WARNINGS
#  "gnu-zero-variadic-macro-arguments"
)

foreach(WARNING_NAME ${IGNORE_WARNINGS})
  set(IGNORE_WARNINGS_FLAGS "${IRGNORE_WARNINGS_FLAGS} -Wno-${WARNING_NAME}")
endforeach()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-pedantic -Wall ${IGNORE_WARNINGS_FLAGS}")

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
