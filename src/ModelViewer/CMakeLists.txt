SET(CURRENT_TARGET_NAME ModelViewer)

find_package(OpenSceneGraph COMPONENTS osgDB osgGA osgUtil osgViewer REQUIRED)
find_package(opencascade REQUIRED)
find_package(osgVerse REQUIRED)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_executable(${CURRENT_TARGET_NAME} ${SRC_FILES} ${HEADER_FILES})
target_include_directories(${CURRENT_TARGET_NAME} 
    PRIVATE 
        $<BUILD_INTERFACE:${osgVerse_INCLUDE_DIRS}>
        $<BUILD_INTERFACE:${OPENSCENEGRAPH_INCLUDE_DIRS}>)
target_link_libraries(${CURRENT_TARGET_NAME} PRIVATE Utilities ${OPENSCENEGRAPH_LIBRARIES} ${osgVerse_LIBRARIES} TKMesh TKSTEP TKIGES imm32.lib opengl32.lib)