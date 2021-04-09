cmake_minimum_required(VERSION 3.10)

project(ssml VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# control where the static and shared libraries are built so that on windows
# we don't need to tinker with the path to run the executable
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external)

# Code Coverage Configuration
add_library(ssml_coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(ssml_coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(ssml_coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(ssml_coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

add_library(ssml INTERFACE)

file(GLOB_RECURSE SSML_SOURCES src/*)
target_sources(ssml INTERFACE ${SSML_SOURCES})
target_include_directories(ssml INTERFACE include/)

target_link_libraries(ssml INTERFACE ssml_coverage_config)

install(TARGETS ssml DESTINATION lib)

# unit test directory
add_subdirectory(test)

# benchmark directory
add_subdirectory(bench)

# packaging system
# linux supported
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/License.txt)
set(CPACK_PACKAGE_VERSION_MAJOR ${SSML_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${SSML_VERSION_MINOR})
include(CPack)
