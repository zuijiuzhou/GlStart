cmake_minimum_required(VERSION 3.10)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${LIBRARY_OUTPUT_PATH})

add_subdirectory(GlHelper)
add_subdirectory(TinyViewer)