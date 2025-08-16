cmake_minimum_required(VERSION 3.1)
project(JV8 LANGUAGES CXX C)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenGl
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

# GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
FetchContent_MakeAvailable(glm)

# Imgui
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.2b
)
FetchContent_MakeAvailable(imgui)

add_library(imgui_lib
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
 "src/tests/Test.h" "src/tests/TestClearColor.h" "src/tests/TestClearColor.cpp")
target_include_directories(imgui_lib PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui_lib PUBLIC glfw glad)

# Src
add_executable(JV8 "src/main.cpp" "src/debug/callback.cpp" "src/VertexBuffer.cpp" "src/IndexBuffer.cpp" "src/VertexArray.cpp" "src/Shader.cpp" "src/Renderer.cpp" "src/vendor/std_image/std_image.cpp" "src/Texture.cpp" "src/tests/TestClearColor.cpp")

# Link
target_include_directories(JV8 PRIVATE ${OPENGL_INCLUDE_DIR} external/glad/include)

target_link_libraries(JV8 PRIVATE OpenGL::GL glad glfw glm imgui_lib)
