#pragma once

#include <GLAD\glad.h>
#include <GLFW/glfw3.h>
#include <nanogui\nanogui.h>
//other includes 
#include <iostream>
#include <Project/Camera.h>
#include <Project/Scene.h>
#include <Project\Command.h>



#pragma region Inputs
//void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode);
//void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset);
//void MouseCallBack(GLFWwindow *window, double xPos, double yPos);
void DoMovement();
#pragma endregion

class Window
{
public:
	Window();
	~Window();
	void InitWindow();
	void InitUI();
	void Update();
	void Render();
	Scene* scene;
	
	GLFWwindow* GetWindow();
	GLuint GetHeight();
	GLuint GetWidth();
	Camera* GetCamera();
	
	glm::vec3 getRay();
	void onCLick();
	void Picker(glm::vec3 rayHit);

private:
	Command command;
	nanogui::FormHelper *gui;
	nanogui::ref<nanogui::Window> nanoguiWindow;
	bool m_bGUIActive = false;
	
	GLFWwindow* window;
	const GLuint m_kiWidth = 1280, m_kiHeight = 720;

};