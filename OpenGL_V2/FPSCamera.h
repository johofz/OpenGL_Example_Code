#pragma once
#include "Camera.h"
class FPSCamera : public Camera
{
public:
	FPSCamera(float32 fov, float32 width, float32 height);

	void GetLineOfSight(float32 xRelative, float32 yRelative);

	void Update() override;

	void MoveFront(float32 increment);
	void MoveSideways(float32 increment);
	void MoveUp(float32 increment);

private:
	glm::vec3 upwards = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 lineOfSight;

	float32 cameraSpeed = 2.0f;

	float32 xRotation;
	float32 yRotation;
	float32 sensitivity = 0.3f;
};

