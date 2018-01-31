/*
FYP Project: 3D Modelller
Nathan Garrett, P15195818
*/

//GLAD
#include <GLAD/glad.h>
//GLFW
#include <GLFW/glfw3.h>
//Other includes
#include <iostream>
#include <Project/Window.h>


int main()
{
	Window window;
	

	window.InitWindow();
	window.Update();
	// cleanup
	glfwTerminate();
	return 0;
}




