#include <Project/Window.h>

Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat flastX = 1280 / 2.0f;
GLfloat flastY = 720 / 2.0f;

GLfloat fDeltaTime = 0.0f;
GLfloat lastframe = 0.0f;

bool abkeys[1024];
bool bFirstMouse = true;

Window::Window()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

}

Window::~Window()
{
}

void Window::InitWindow()
{

	

	// initialise a window and let GLFW know that it should target opengl version 4.3
	glfwInit();
	window = glfwCreateWindow(m_kiWidth, m_kiHeight, "3DModeller", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	// make this new window our current context, THEN try to initialise GLAD function ptrs
	glfwMakeContextCurrent(window);
	//set callbacks
	glfwSetKeyCallback(window, KeyCallBack);
	glfwSetCursorPosCallback(window, MouseCallBack);
	glfwSetScrollCallback(window, ScrollCallBack);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//Glad init
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
	}
	//Check if window
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}


	//shader setup for basic shader
	glm::mat4 model(1.0f);
	program.compileShader("res/defaultShader.vert");
	program.compileShader("res/defaultShader.frag");
	program.link();
	program.validate();
	program.use();
	//set uniform vars
	program.setUniform("colour", glm::vec3(0.75, 0.0, 0.75));
	
	//simple triangle set up to test mouse click


	Update();
	
}

void Window::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		fDeltaTime = currentFrame - lastframe;
		lastframe = currentFrame;
		// clear the screen to a green colour
		
		glfwPollEvents();
		DoMovement();
		Render();
		// swap buffers i.e. draw to screen
		glfwSwapBuffers(window);
		getRay();
		
	}
}

void Window::Render()
{
	static const GLfloat g_vertex_buffer_data[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f,
	};
	// This will identify our vertex buffer
	GLuint vertexbuffer;
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);



}
#pragma region Getters
GLFWwindow * Window::GetWindow()
{
	return window;
}

GLuint Window::GetWidth()
{
	return m_kiWidth;
}

Camera * Window::GetCamera()
{
	return camera;
}

GLuint Window::GetHeight()
{
	return m_kiHeight;
}
#pragma endregion

#pragma region Input

void KeyCallBack(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
		{
			abkeys[key] = true;
		}

		else if (action == GLFW_RELEASE)
		{
			abkeys[key] = false;
		}
	}

	if (abkeys[GLFW_KEY_LEFT_CONTROL] && abkeys[GLFW_KEY_R])
	{
		camera->ResetCamera();
	}

}
void ScrollCallBack(GLFWwindow * window, double xOffset, double yOffset)
{	
		std::cout << "SCB" << std::endl;
		camera->ScrollProc(yOffset);
}

void MouseCallBack(GLFWwindow * window, double xPos, double yPos)
{
	if (abkeys[GLFW_KEY_LEFT_SHIFT])
	{
		std::cout << "MCB" << std::endl;
		if (bFirstMouse)
		{
			flastX = xPos;
			flastY = yPos;
			bFirstMouse = false;
		}
		GLfloat xOffset = xPos - flastX;
		GLfloat yOffset = flastY - yPos;

		

		camera->MouseProc(xOffset, yOffset);
	}
	flastX = xPos;
	flastY = yPos;
	
}

void DoMovement()
{
	if (abkeys[GLFW_KEY_LEFT_SHIFT])
	{
		std::cout << "Do movement" << std::endl;
		if (abkeys[GLFW_KEY_W] || abkeys[GLFW_KEY_UP])
		{
			camera->KeyProc(FORWARD, fDeltaTime);
		}
		if (abkeys[GLFW_KEY_A] || abkeys[GLFW_KEY_LEFT])
		{
			camera->KeyProc(LEFT, fDeltaTime);
		}
		if (abkeys[GLFW_KEY_S] || abkeys[GLFW_KEY_DOWN])
		{
			camera->KeyProc(BACK, fDeltaTime);
		}
		if (abkeys[GLFW_KEY_D] || abkeys[GLFW_KEY_RIGHT])
		{
			camera->KeyProc(RIGHT, fDeltaTime);
		}
		std::cout << camera->GetCamPos().x<< camera->GetCamPos().y << camera->GetCamPos().z<< std::endl;
	}
};
#pragma endregion

#pragma region MouseClick

glm::vec3 Window::getRay()
{
	//step one get viewport co-ords
	glm::vec2 clickPos(flastX, flastY);
	glm::vec3 WorldClickPos;
	glm::vec4 ray_clip;
	glm::vec4 ray_eye;
	//step two 3d normalised device co-ords
	WorldClickPos.x = (2.0f * clickPos.x) / m_kiWidth - 1.0f;
	WorldClickPos.y = 1.0f - (2.0f * clickPos.y) / m_kiHeight;
	WorldClickPos.z = 1.0f;
	//step 3 4d homogenous clip co-ords
	ray_clip = glm::vec4(WorldClickPos.x, WorldClickPos.y, -1.0f, 1.0f);
	//step 4 4d eye(camera) co-ords
	ray_eye = glm::inverse(camera->GetProjectionMatrix()) * ray_clip;
	ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);
	//step 5 4d world co-ordinates
	glm::vec3 ray_world; 
	ray_world.x = (glm::inverse(camera->GetViewMatrix())* ray_eye).x;
	ray_world.y = (glm::inverse(camera->GetViewMatrix())* ray_eye).y;
	ray_world.z = (glm::inverse(camera->GetViewMatrix())* ray_eye).z;

	std::cout<< ray_world.x <<ray_world.y<<ray_world.z<< std::endl;
	return ray_world;
}

void Window::onCLick()
{
}

#pragma endregion



