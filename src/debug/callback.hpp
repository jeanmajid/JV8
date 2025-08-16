#ifdef _DEBUG
#pragma once
#include <glad/glad.h>

void APIENTRY openglCallbackFunction(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam);
#endif

