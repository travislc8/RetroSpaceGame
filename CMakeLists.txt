cmake_minimum_required(VERSION 3.10)
project(RaylibTest)
add_executable(main main.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(main PRIVATE ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# -lopengl32
find_package(OpenGL REQUIRED)
target_link_libraries(main PRIVATE OpenGL::GL)

# -lgdi32
target_link_libraries(main PRIVATE gdi32)

# -lwinmm
target_link_libraries(main PRIVATE winmm)

#-lopengl32 -lgdi32 -lwinmm
