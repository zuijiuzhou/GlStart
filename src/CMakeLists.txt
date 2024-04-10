include_directories(${CMAKE_CURRENT_SOURCE_DIR})
link_directories(${LIBRARY_OUTPUT_PATH})

add_subdirectory(Utilities)
add_subdirectory(GlHelper)
add_subdirectory(AnyRenderer)
add_subdirectory(ModelViewer)