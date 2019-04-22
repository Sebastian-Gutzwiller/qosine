# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()

# Now simply link against gtest or gtest_main as needed. Eg
cmake_minimum_required(VERSION 2.8)

cmake_policy(SET CMP0048 NEW)
project(Qosine VERSION 0.1)
configure_file("${PROJECT_SOURCE_DIR}/QosineConfig.h.in" "${CMAKE_CURRENT_BINARY_DIR}/QosineConfig.h")
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(${PROJECT_NAME} "QosineRunUnitTests.cpp" "QosineWaveformLister.cpp")

target_link_libraries(${PROJECT_NAME} gtest)

cmake_policy(SET CMP0054 NEW)
include(GoogleTest)

gtest_add_tests(TARGET ${PROJECT_NAME})
#gtest_discover_tests(${PROJECT_NAME})

#enable_testing()
#add_test(QosineUsage ${PROJECT_NAME})
#set_tests_properties(QosineUsage PROPERTIES PASS_REGULAR_EXPRESSION "Version")
