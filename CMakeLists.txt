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

if(CODE_COVERAGE)
if("${CMAKE_C_COMPILER_ID}" MATCHES "[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "[Cc]lang")
  message("Building with llvm Code Coverage Tools")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
else()
  message(FATAL_ERROR "Code coverage requires Clang. Aborting.")
endif()
endif()

configure_file("${PROJECT_SOURCE_DIR}/QosineConfig.h.in" "${PROJECT_SOURCE_DIR}/QosineConfig.h")
#include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/QosineRunUnitTests.cpp" "${PROJECT_SOURCE_DIR}/QosineWaveformLister.cpp")

target_link_libraries(${PROJECT_NAME} gtest)

enable_testing()

cmake_policy(SET CMP0054 NEW)
include(GoogleTest)

gtest_discover_tests(${PROJECT_NAME})

if(CODE_COVERAGE)
if("${CMAKE_C_COMPILER_ID}" MATCHES "[Cc]lang" OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "[Cc]lang")
  add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ./${PROJECT_NAME}
    COMMAND llvm-profdata merge -sparse default.profraw -o ../${PROJECT_NAME}.profdata
    COMMAND llvm-cov report ./${PROJECT_NAME} -instr-profile=../${PROJECT_NAME}.profdata)
endif()
endif()

#add_test(QosineUsage ${PROJECT_NAME})
#set_tests_properties(QosineUsage PROPERTIES PASS_REGULAR_EXPRESSION "Version")
