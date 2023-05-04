# CMakeList.txt : CMake project for CMakeProj, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project ("CMakeProj" VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

# Add source to this project's executable.
add_executable (CMakeProj "CMakeProj.cpp")
add_library(CMakeProj_lib "lib.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VESRION})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProj PROPERTY CXX_STANDARD 20)
  set_property(TARGET CMakeProj_lib PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(CMakeProj_lib
    PRIVATE ${CMAKE_BINARY_DIR}
)

target_link_libraries(CMakeProj PRIVATE
    CMakeProj_lib
)

#Testing

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  CMakeProj_test
  tests.cpp
)
target_link_libraries(
  CMakeProj_test
  GTest::gtest_main
  CMakeProj_lib
)

include(GoogleTest)
gtest_discover_tests(CMakeProj_test)