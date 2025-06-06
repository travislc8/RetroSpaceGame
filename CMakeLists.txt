cmake_minimum_required(VERSION 3.10)
project(RaylibTest)

file(GLOB SOURCES src/Logic/*.cpp src/Levels/*.cpp  src/Components/*.cpp src/*.cpp)
add_executable(main ${SOURCES})

set(FETCHCONTENT_BASE_DIR "../vendor")
include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

####################################################
# raylib
####################################################
#FetchContent_MakeAvailable(raylib)
find_package(raylib QUIET)

set(RAYLIB_VERSION 5.5)
if (NOT raylib_FOUND) 
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
  endif()
endif()
target_link_libraries(main PRIVATE raylib)

####################################################
# gtest
####################################################
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  run_test
  test/test.cpp
)
target_link_libraries(
  run_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_test)

####################################################
# linked library setup
####################################################
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# -lopengl32
find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE OpenGL::GL)

# -lgdi32
#target_link_libraries(main PRIVATE gdi32)

# -lwinmm
#target_link_libraries(main PRIVATE winmm)

#-lopengl32 -lgdi32 -lwinmm

# Define a macro globally
add_compile_definitions(MODE=0)
