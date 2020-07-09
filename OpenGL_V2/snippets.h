#pragma once


const uint32 shapeCount = 1;
Shape* shapes[shapeCount];

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(-100, 100);

for (int i = 0; i < shapeCount; i++) {
	float32 x = dis(gen);
	float32 y = dis(gen);
	float32 z = dis(gen);

	glm::vec3 direction = glm::normalize(glm::vec3(x, y, z));
	float32 distance = 1.0f;
	glm::vec3 centerPnt = direction * distance;

	shapes[i] = new Cube(centerPnt, 1.0f);
}