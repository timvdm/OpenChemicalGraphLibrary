#
# Copy header files
#
# Example:
#
# set(FOO_HDRS
#   foo.h
#   foo/bar.h
# )
#
# copy_headers(${FOO_HDRS} foolib)
#
# This will copy the headers to ${CMAKE_BUILD_DIR}/include/foolib/
#
function(copy_headers HEADER_FILES COMPONENT)
  #message("copy_headers(${HEADER_FILES}, ${COMPONENT})")

  if(UNIX)
    set(header_cmd "create_symlink")
  else()
    set(header_cmd "copy_if_different")
  endif()

  foreach(HEADER_FILE ${HEADER_FILES})
    # make sure destination directory exists
    get_filename_component(HEADER_DIR ${HEADER_FILE} DIRECTORY)
    set(dest_dir "${CMAKE_BINARY_DIR}/include/${COMPONENT}/${HEADER_DIR}")
    file(MAKE_DIRECTORY ${dest_dir})

    # copy header file
    set(from "${CMAKE_CURRENT_SOURCE_DIR}/${HEADER_FILE}")
    set(dest "${CMAKE_BINARY_DIR}/include/${COMPONENT}/${HEADER_FILE}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E ${header_cmd} "${from}" "${dest}")
  endforeach(HEADER_FILE)

endfunction()

#
# Add a unit test
#
# Example:
#
# add_gtest(foo.cpp)
# add_gtest(foo.cpp foolib)
# add_gtest(foo.cpp foolib barlib)
#
function(add_gtest TEST_SOURCE)
  #message(STATUS "adding test: ${TEST_SOURCE} - libraries: ${ARGV1} ${ARGV2} ${ARGV3} ${ARGV4}")
  get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
  add_executable(${TEST_NAME}_test ${TEST_SOURCE})
  target_link_libraries(${TEST_NAME}_test ${CMAKE_THREAD_LIBS_INIT} ${GTEST_BOTH_LIBRARIES} ${ARGV1} ${ARGV2} ${ARGV3} ${ARGV4})
  add_test(${TEST_NAME}_test ${TEST_NAME}_test)
endfunction()
