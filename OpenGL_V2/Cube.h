#pragma once
#include "Shape.h"

class Cube : public Shape
{
public:
	Cube(glm::vec3 center, float32 width, Shader* shader);

	void UpdateVerts();
	void Move(glm::vec3 translation) override;

	void Draw() override;

private:

	float32 width;
	float32 height;
	float32 depth;

	uint32 numVerts = 24;
	Vertex verts[24];

	uint32 numIndices = 36;
	uint32 indices[36];
};

