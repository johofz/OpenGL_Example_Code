#include "LightCube.h"

LightCube::LightCube(const glm::vec3& center, float32 width, const glm::vec3& color, Shader* shader)
	: Cube (center, width, color, shader)
{
}

