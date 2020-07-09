#pragma once
#include "defines.h"
#include <GL/glew.h>


class IndexBuffer
{
public:
	IndexBuffer(void* data, uint32 numIndices, uint8 elementSize);
	~IndexBuffer();

    void Bind() const;
	void Unbind() const;

	GLuint GetNumIndices();

private:
	GLuint bufferID;
	GLuint numIndices;
};

