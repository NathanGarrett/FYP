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

//triangle struct for picker
struct Triangle
{
	glm::vec3 vertA;
	glm::vec3 vertB;
	glm::vec3 vertC;
};

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
	void PrepModel();

	glm::vec3 getRayVector();
	glm::vec3 getRayOrigin();
	void onCLick();
	void Picker(glm::vec3 rayVector,glm::vec3 rayOrigin);
	bool RayIntersectsTriangle(glm::vec3 rayOrigin, glm::vec3 rayVector, Triangle inTriangle, glm::vec3& outIntersectionPoint);
private:
	Command command;
	std::vector<int> indices;
	string sfileName;
	nanogui::FormHelper *guiTransform; 
	nanogui::FormHelper *guiToolbar;
	nanogui::FormHelper *guiImporterExporter;
	nanogui::ref<nanogui::Window> guiTransformWindow;
	nanogui::ref<nanogui::Window> guiToolbarWindow;
	nanogui::ref<nanogui::Window> guiImporterExporterWindow;
	bool m_bGUIActive = false;
	
	GLFWwindow* window;
	const GLuint m_kiWidth = 1280, m_kiHeight = 720;
	double EPSILON = 0.0000001;
};