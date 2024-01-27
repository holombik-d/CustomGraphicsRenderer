cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(PROJECT_NAME CustomGraphicsRenderer)
set(CMAKE_CXX_STANDART 17)

project(${PROJECT_NAME})

add_executable(CustomGraphicsRenderer src/main.cpp
				src/tools/Logger.h
				src/tools/Logger.cpp
				src/Window/Window.h
				src/Window/Window.cpp
				src/tools/IInputHandler.cpp
				src/tools/IInputHandler.h
				src/tools/InputHandler.h
				src/tools/InputHandler.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

include_directories(external/glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)