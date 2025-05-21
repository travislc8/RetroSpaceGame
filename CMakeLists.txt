cmake_minimum_required(VERSION 3.10)
project(RaylibTest)
add_executable(main src/main.cpp)

set(FETCHCONTENT_BASE_DIR "../vendor")
include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# raylib
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

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE raylib)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# -lopengl32
find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE OpenGL::GL)

# -lgdi32
#target_link_libraries(main PRIVATE gdi32)

# -lwinmm
#target_link_libraries(main PRIVATE winmm)

#-lopengl32 -lgdi32 -lwinmm

