#pragma once
#include <vector>
#include <GLAD/glad.h>
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
enum Camera_Movement
{
	FORWARD,
	BACK,
	LEFT,
	RIGHT
};

const GLfloat fYaw = -90.0f;
const GLfloat fPitch = 0.0f;
const GLfloat fSpeed = 6.0f;
const GLfloat fSensitivity = 0.25f;
const GLfloat fZoom = 45.0f;

class Camera
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = fYaw , GLfloat Pitch = fPitch);
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat UpX, GLfloat UpY, GLfloat UpZ, GLfloat yaw, GLfloat pitch);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();
	GLfloat GetZoom() { return m_fZoom; };
	GLfloat SetZoom(GLfloat zoom) { m_fZoom = zoom; };
	glm::vec3 GetCamPos() { return m_position; };
	void ResetCamera();
	~Camera() {};
#pragma region CameraControls
	void KeyProc(Camera_Movement direction, GLfloat dTime);
	void MouseProc(GLfloat xOffset, GLfloat yOffset, GLboolean constrainpitch = true);
	void ScrollProc(GLfloat yOffset, GLboolean constrainpitch = true);
#pragma endregion


private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	GLfloat m_fYaw = -90.f;
	GLfloat m_fPitch = 0.f;
	GLfloat m_fSpeed = 6.f;
	GLfloat m_fSensitivity = 0.25f;
	GLfloat m_fZoom = 45.f;

	void updateCameraVectors();
};


