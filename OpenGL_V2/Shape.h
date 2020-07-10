#pragma once
#include "defines.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class Shape
{
public:
	virtual ~Shape();
	
	void CreateVertexArray(void* data, uint32 numVerts);
	void CreateIndexBuffer(void* data, uint32 numIndices, uint8 size);

	void Bind();
	void Unbind();

	virtual void Move(glm::vec3 translation);
	virtual void Draw();

	VertexBuffer* GetVertexBuffer();
	IndexBuffer* GetIndexBuffer();
	glm::vec3 GetPosition();
	glm::vec3 GetInitialPosition();

	void UpdateVertexBuffer(void* data);
	virtual void ShaderSetColor(glm::vec3 color);

protected:
	glm::vec3 m_position;
	glm::vec3 m_initialPosition;

	glm::vec3 m_color;

	Shader* m_shader;
	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;
};

