#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
	Cube(const glm::vec3& center, float32 width, const glm::vec3& color, Shader* shader);

	void UpdateVerts();
	void Move(glm::vec3 translation) override;

	void Draw() override;

protected:

	float32 m_width;

	uint32 m_numVerts = 24;
	Vertex m_verts[24];

	uint32 m_numIndices = 36;
	uint32 m_indices[36];
};

