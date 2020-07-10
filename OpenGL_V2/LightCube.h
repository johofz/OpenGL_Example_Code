#pragma once
#include "Cube.h"
class LightCube : public Cube
{
public:
	LightCube(const glm::vec3& center, float32 width, const glm::vec3& color, Shader* shader);
};

