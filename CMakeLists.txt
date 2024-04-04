cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME CustomGraphicsRenderer)
set(CMAKE_CXX_STANDART 17)

project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

include_directories(external/glm)

# Include the entire src directory
include_directories(${CMAKE_SOURCE_DIR}/src)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)