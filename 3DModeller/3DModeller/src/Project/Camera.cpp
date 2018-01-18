#include "Project\Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	m_position = position;
	m_worldUp = up;
	m_fYaw = yaw;
	m_fPitch = pitch;
	updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat UpX, GLfloat UpY, GLfloat UpZ, GLfloat yaw, GLfloat pitch)
{
	m_position = glm::vec3(posX, posY, posZ);
	m_worldUp = glm::vec3(UpX, UpY, UpZ);
	m_fYaw = yaw;
	m_fPitch = pitch;
	updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_front, m_worldUp);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return glm::perspectiveFov(fZoom, 10.f, 10.f, 1.f, 100.f);
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));
	front.y = sin(glm::radians(m_fPitch));
	front.z = sin(glm::radians(m_fYaw)) * cos(glm::radians(m_fPitch));

	m_front = glm::normalize(front);
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_worldUp = glm::normalize(glm::cross(m_right, m_front));
}
#pragma region Camera Controls

void Camera::ResetCamera()
{
	m_position = glm::vec3(0.0f, 0.0f, 3.0f);
	updateCameraVectors();
}

void Camera::KeyProc(Camera_Movement direction, GLfloat dTime)
{
	GLfloat fVelocity = m_fSpeed*dTime;

	if (direction == FORWARD)
	{
		this->m_position += m_front * fVelocity;

	}

	if (direction == BACK)
	{
		this->m_position -= m_front * fVelocity;
	}

	if (direction == LEFT)
	{
		this->m_position -= m_right * fVelocity;

	}

	if (direction == RIGHT)
	{
		this->m_position += m_right * fVelocity;
	}

}

void Camera::MouseProc(GLfloat xOffset, GLfloat yOffset, GLboolean constrainpitch)
{
	xOffset *= m_fSensitivity;
	yOffset *= m_fSensitivity;
	m_fYaw += xOffset;
	m_fPitch += yOffset;

	if (constrainpitch)
	{
		if (m_fPitch > 89.0f)
		{
			m_fPitch = 89.0f;
		}

		if (m_fPitch < -89.0f)
		{
			m_fPitch = -89.0f;
		}
		this->updateCameraVectors();
	}
}

void Camera::ScrollProc(GLfloat yOffset, GLboolean constrainpitch)
{
	if (m_fZoom >= 1.0f && m_fZoom <= 45.0f)
	{
		m_fZoom -= yOffset;
	}

	if (m_fZoom < 1.0f)
	{
		m_fZoom = 1.0f;
	}


	if (m_fZoom >= 45.0f)
	{
		m_fZoom = 45.0f;
	}
}
#pragma endregion


