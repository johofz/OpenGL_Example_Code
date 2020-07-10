#pragma once
#include "Camera.h"
class FPSCamera : public Camera
{
public:
	FPSCamera(float32 fov, float32 width, float32 height);

	void GetLineOfSight(float32 xRelative, float32 yRelative);

	void UpdateView();

	const glm::vec3& LineOfSight() const { return m_lineOfSight; }

	void MoveFront(float32 increment);
	void MoveSideways(float32 increment);
	void MoveUp(float32 increment);

private:
	glm::vec3 m_upwards = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 m_lineOfSight;

	float32 m_cameraSpeed = 2.0f;

	float32 m_xRotation;
	float32 m_yRotation;
	float32 m_sensitivity = 0.3f;
};

