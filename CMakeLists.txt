cmake_minimum_required(VERSION 3.1)
project(JV8 LANGUAGES CXX C)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)

# Glfw
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# Glad
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# Src
add_executable(JV8
    src/main.cpp
)

# Link
target_include_directories(JV8 PRIVATE ${OPENGL_INCLUDE_DIR} external/glad/include)

target_link_libraries(JV8 PRIVATE OpenGL::GL glad glfw)
