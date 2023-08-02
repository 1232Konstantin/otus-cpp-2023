# CMakeList.txt : CMake project for Allocator, include source and define
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

project ("Allocator" VERSION ${PROJECT_VESRION})

# Add source to this project's executable.
add_executable (Allocator "allocator.cpp")
add_library(Timus_lib "timus.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VESRION})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Allocator PROPERTY CXX_STANDARD 17)
  set_property(TARGET Timus_lib PROPERTY CXX_STANDARD 17)
endif()

target_link_libraries(Allocator PRIVATE
    Timus_lib
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
    Timus_test
    test_timus.cpp
)
target_link_libraries(
    Timus_test
    GTest::gtest_main
    Timus_lib
)

include(GoogleTest)
gtest_discover_tests(Timus_test)