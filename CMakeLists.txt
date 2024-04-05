cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME CustomGraphicsRenderer)
set(CMAKE_CXX_STANDART 17)

project(${PROJECT_NAME})

# Add glad source files
file(GLOB_RECURSE GLAD_SOURCES "external/glad/src/*.c")

# Add your project source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD_SOURCES}) # Add glad sources here

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

# Link against OpenGL library
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)

include_directories(external/glm)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/external/glad/include) # Include glad include directory

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
