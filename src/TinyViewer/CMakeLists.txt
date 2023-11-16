cmake_minimum_required(VERSION 3.9)

SET(CURRENT_PROJ_NAME TinyViewer)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR} *.cpp *.h)

add_executable(${CURRENT_PROJ_NAME} ${SRC_FILES} ${GLAD_SRC_FILES})

target_link_libraries(${CURRENT_PROJ_NAME} glfw glm::glm)