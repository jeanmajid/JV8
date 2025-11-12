#pragma once
#include <vector>
#include <glad/glad.h>
#include <iostream>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalised;

    static unsigned int GetSizeOfType(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        std::cerr << "Unknown type passed into GetSizeOfType!" << std::endl;
        return 0;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;

public:
    VertexBufferLayout() : stride(0) {
    };

    ~VertexBufferLayout() {
    };

    template<typename T>
    void push(unsigned int count);

    inline std::vector<VertexBufferElement> getElements() const { return elements; };
    inline unsigned int getStride() const { return stride; };
};

template<typename t>
void VertexBufferLayout::push(unsigned int count) {
    static_assert(false, "Type not supported");
}

template<>
inline void VertexBufferLayout::push<float>(unsigned int count) {
    elements.push_back({ GL_FLOAT, count, GL_FALSE });
    stride += sizeof(GLfloat) * count;
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count) {
    elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    stride += sizeof(GLuint) * count;
}

template<>
inline void VertexBufferLayout::push<unsigned char>(unsigned int count) {
    elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    stride += sizeof(GLbyte) * count;
}