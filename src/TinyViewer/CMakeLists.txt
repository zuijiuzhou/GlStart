cmake_minimum_required(VERSION 3.9)

include_directories(${LIB_GLEW_DIR}/include)  
include_directories(${LIB_GLFW_DIR}/include)
include_directories(${LIB_GLM_DIR})    
include_directories(${LIB_STB_DIR})    

SET(CURRENT_PROJ TinyViewer)

link_directories(${LIB_GLEW_DIR}/lib)  
link_directories(${LIB_GLFW_DIR}/lib-vc2022)
link_directories(${LIB_GLM_DIR}/lib/debug)   

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR} *.cpp *.h)

add_executable(${CURRENT_PROJ} ${SRC_FILES})

target_link_libraries(${CURRENT_PROJ} glew32.lib)