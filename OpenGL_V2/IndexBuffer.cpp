#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, uint32 numIndices, uint8 elementSize)
{
    this->numIndices = numIndices;

    GLCall(glGenBuffers(1, &bufferID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_DYNAMIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &bufferID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

GLuint IndexBuffer::GetNumIndices()
{
    return numIndices;
}
