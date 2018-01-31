#pragma once
//GLAD
#include <GLAD\glad.h>
//GLFW
#include <GLFW\glfw3.h>
//other includes 
#include <iostream>
#include <Project/Camera.h>
#include <Project/Scene.h>


#pragma region Inputs
void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode);
void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset);
void MouseCallBack(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
#pragma endregion

class Window
{
public:
	Window();
	~Window();
	void InitWindow();
	void Update();
	void Render();
	Scene* scene;
	GLFWwindow* GetWindow();
	GLuint GetHeight();
	GLuint GetWidth();
	Camera* GetCamera();
	glm::vec3 getRay();
	void onCLick();
private:
	GLFWwindow* window;
	const GLuint m_kiWidth = 1280, m_kiHeight = 720;
};