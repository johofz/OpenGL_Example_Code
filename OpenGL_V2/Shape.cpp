#include "Shape.h"


Shape::~Shape()
{
}

void Shape::CreateVertexArray(void* data, uint32 numVerts)
{
	m_vertexBuffer = new VertexBuffer(data, numVerts);
}

void Shape::CreateIndexBuffer(void* data, uint32 numIndices, uint8 size)
{
	m_indexBuffer = new IndexBuffer(data, numIndices, size);
}

void Shape::Bind()
{
	m_shader->Bind();
	m_vertexBuffer->Bind();
	m_indexBuffer->Bind();
}

void Shape::Unbind()
{
	m_indexBuffer->Unbind();
	m_vertexBuffer->Unbind();
	m_shader->Unbind();
}

void Shape::Move(glm::vec3 translation)
{
}

void Shape::Draw()
{
}

VertexBuffer* Shape::GetVertexBuffer()
{
	return m_vertexBuffer;
}

IndexBuffer* Shape::GetIndexBuffer()
{
	return m_indexBuffer;
}

glm::vec3 Shape::GetPosition()
{
	return m_position;
}

glm::vec3 Shape::GetInitialPosition()
{
	return m_initialPosition;
}

void Shape::UpdateVertexBuffer(void* data)
{
	m_vertexBuffer->Update(data);
}

void Shape::ShaderSetColor(glm::vec3 color)
{
	m_color = color;
	m_shader->SetUniform(m_shader->GetUniformLoc("u_objectColor"), m_color);
}

