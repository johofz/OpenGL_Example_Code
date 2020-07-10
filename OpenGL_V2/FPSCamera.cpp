#include "FPSCamera.h"

FPSCamera::FPSCamera(float32 fov, float32 width, float32 height) : Camera(fov, width, height)
{
	m_xRotation = -90.0f;
	m_yRotation = 0.0f;

	GetLineOfSight(0.0f, 0.0f);
	UpdateView();
}

void FPSCamera::GetLineOfSight(float32 xRelative, float32 yRelative)
{
	m_xRotation += xRelative * m_sensitivity;
	m_yRotation -= yRelative * m_sensitivity;

	if (m_yRotation > 89.9f)
		m_yRotation = 89.9f;
	if (m_yRotation < -89.9f)
		m_yRotation = -89.9f;

	m_lineOfSight.x = cos(glm::radians(m_xRotation)) * cos(glm::radians(m_yRotation));
	m_lineOfSight.y = sin(glm::radians(m_yRotation));
	m_lineOfSight.z = sin(glm::radians(m_xRotation)) * cos(glm::radians(m_yRotation));

	m_lineOfSight = glm::normalize(m_lineOfSight);

	UpdateView();
}

void FPSCamera::UpdateView()
{
	m_view = glm::lookAt(m_position, m_position + m_lineOfSight, m_upwards);
}

void FPSCamera::MoveFront(float32 increment)
{
	glm::vec3 direction = glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f) * m_lineOfSight);
	Translate(direction * increment * m_cameraSpeed);
}

void FPSCamera::MoveSideways(float32 increment)
{
	glm::vec3 direction = glm::cross(m_lineOfSight, m_upwards);
	Translate(direction * increment * m_cameraSpeed);
}

void FPSCamera::MoveUp(float32 increment)
{
	Translate(m_upwards * increment * m_cameraSpeed);
}
