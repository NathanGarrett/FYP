//#pragma once
////#include <Project/Camera.h>
//#include <Project/Window.h>
//#include <vector>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//void KeyCallBack(GLFWwindow *window, int key, int scancode, int action, int mode);
//void ScrollCallBack(GLFWwindow *window, double xOffset, double yOffset);
//void MouseCallBack(GLFWwindow *window, double xPos, double yPos);
//
//class InputHandler : public Window
//{
//public:
//	InputHandler() 
//	{
//		std::cout << "Inputhandler:Constructor" << std::endl;
//		m_bFirstMouse = true;
//		m_flastX = 1280 / 2;
//		m_flastY = 720 / 2;
//		m_fDeltaTime = 0;
//		camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
//
//
//
//
//	};
//	~InputHandler() {};
//
//	void DoMovement()
//	{
//		if (m_abkeys[GLFW_KEY_W] || m_abkeys[GLFW_KEY_UP])
//		{
//			camera->KeyProc(FORWARD, m_fDeltaTime);
//		}
//		if (m_abkeys[GLFW_KEY_A] || m_abkeys[GLFW_KEY_LEFT])
//		{
//			camera->KeyProc(LEFT, m_fDeltaTime);
//		}
//		if (m_abkeys[GLFW_KEY_S] || m_abkeys[GLFW_KEY_DOWN])
//		{
//			camera->KeyProc(BACK, m_fDeltaTime);
//		}
//		if (m_abkeys[GLFW_KEY_D] || m_abkeys[GLFW_KEY_RIGHT])
//		{
//			camera->KeyProc(RIGHT, m_fDeltaTime);
//		}
//	};
//	
//
//
//	bool	m_abkeys[1024];
//	bool	m_bFirstMouse;
//	GLfloat m_flastX;
//	GLfloat m_flastY;
//	GLfloat m_fDeltaTime;
//};
//
//InputHandler handler;
//
//void KeyCallBack(GLFWwindow * window, int key, int scancode, int action, int mode)
//{
//
//	std::cout << "KCB" << std::endl;
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//
//	if (key >= 0 && key <= 1024)
//	{
//		if (action == GLFW_PRESS)
//		{
//			handler.m_abkeys[key] = true;
//		}
//
//		else if (action == GLFW_RELEASE)
//		{
//			handler.m_abkeys[key] = false;
//		}
//	}
//}
//void ScrollCallBack(GLFWwindow * window, double xOffset, double yOffset)
//{
//
//	handler.camera->ScrollProc(yOffset);
//}
//
//void MouseCallBack(GLFWwindow * window, double xPos, double yPos)
//{
//
//
//		if (handler.m_bFirstMouse)
//		{
//			handler.m_flastX = xPos;
//			handler.m_flastY = yPos;
//			handler.m_bFirstMouse = false;
//		}
//		GLfloat xOffset = xPos - handler.m_flastX;
//		GLfloat yOffset = handler.m_flastY - yPos;
//
//		handler.m_flastX = xPos;
//		handler.m_flastY = yPos;
//
//		handler.camera->MouseProc(xOffset, yOffset);
//	
//}
//
