#include <Project/Window.h>

Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));
GLfloat flastX = 1280 / 2.0f;
GLfloat flastY = 720 / 2.0f;

GLfloat fDeltaTime = 0.0f;
GLfloat lastframe = 0.0f;

bool abkeys[1024];
bool bFirstMouse = true;

nanogui::Screen* screen = nullptr;

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



#pragma region nanoCallBacks
	glfwSetCursorPosCallback(window,[](GLFWwindow *, double x, double y)
	{
		screen->cursorPosCallbackEvent(x, y);
		GLfloat	fxPos = static_cast<GLfloat>(x);
		GLfloat	fyPos = static_cast<GLfloat>(y);

		if (abkeys[GLFW_KEY_LEFT_SHIFT])
		{

			if (bFirstMouse)
			{
				flastX = fxPos;
				flastY = fyPos;
				bFirstMouse = false;
			}
			GLfloat xOffset = fxPos - flastX;
			GLfloat yOffset = flastY - fyPos;



			camera->MouseProc(xOffset, yOffset);
		}
		flastX = fxPos;
		flastY = fyPos;

	}
	);

	glfwSetMouseButtonCallback(window,[](GLFWwindow *, int button, int action, int modifiers) 
	{
		screen->mouseButtonCallbackEvent(button, action, modifiers);
	}
	);

	glfwSetKeyCallback(window,[](GLFWwindow *, int key, int scancode, int action, int mods) 
	{
		screen->keyCallbackEvent(key, scancode, action, mods);
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
	}
	);

	glfwSetCharCallback(window,[](GLFWwindow *, unsigned int codepoint) 
	{
		screen->charCallbackEvent(codepoint);
	}
	);

	glfwSetDropCallback(window,[](GLFWwindow *, int count, const char **filenames)
	{
		screen->dropCallbackEvent(count, filenames);
	});

	glfwSetScrollCallback(window,[](GLFWwindow *, double x, double y) 
	{
		screen->scrollCallbackEvent(x, y);
	});

	glfwSetFramebufferSizeCallback(window,[](GLFWwindow *, int width, int height) 
	{
		screen->resizeCallbackEvent(width, height);
	});
#pragma endregion
	
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
	

	scene = new Scene();
	scene->initScene(*camera);
	
	screen = new nanogui::Screen();
	screen->initialize(window, true);
	
	gui = new nanogui::FormHelper(screen);
	nanoguiWindow = gui->addWindow(Eigen::Vector2i(10, 10), "Transform");

}

void Window::InitUI()
{
	
	if (!m_bGUIActive)
	{
		gui->addGroup("Scale");
		gui->addVariable("X", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_scale.x, true);
		gui->addVariable("Y", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_scale.y,true);
		gui->addVariable("Z", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_scale.z,true);
		gui->addGroup("Position");
		gui->addVariable("X", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_position.x,true);
		gui->addVariable("Y", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_position.y,true);
		gui->addVariable("Z", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_position.z,true);
		gui->addGroup("Rotation");
		gui->addVariable("Roll", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_orientation.x,true);
		gui->addVariable("Pitch", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_orientation.y,true);
		gui->addVariable("Yaw", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_orientation.z,true);
		
		m_bGUIActive = true;
		screen->updateFocus(nanoguiWindow);
	}
	screen->setVisible(true);
	screen->performLayout();
	nanoguiWindow->setPosition(nanogui::Vector2i(10, 10));
	
	gui->refresh();
	
}

void Window::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		fDeltaTime = currentFrame - lastframe;
		lastframe = currentFrame;
		
		glClearColor(0.5f, 0.5f, 0.5f, 0.f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				
		glfwWaitEvents();

		DoMovement();
		glDisable(GL_DEPTH_TEST);

		
		screen->drawWidgets();
		screen->drawContents();
		glEnable(GL_DEPTH_TEST);
		Render();

		// swap buffers i.e. draw to screen
		glfwSwapBuffers(window);
		//onCLick();
		
	}
}

void Window::Render()
{
	if (scene->m_Objects.size() < 1) { scene->GenModel("shape.obj"); }
	if (abkeys[GLFW_KEY_M])
	{
		std::cout << "M key" << std::endl;
		//command.MirrorGeometryYZ(&scene->m_Objects[0]->getComponent<ModelComponent>()->getModel(), 7);
		//command.MirrorGeometryZX(&scene->m_Objects[0]->getComponent<ModelComponent>()->getModel(),1);
		command.MirrorGeometryXY(&scene->m_Objects[0]->getComponent<ModelComponent>()->getModel(), 2.5);
	}
	if (abkeys[GLFW_KEY_LEFT_CONTROL] && abkeys[GLFW_KEY_TAB])
	{
		scene->CycleFoci();
		std::cout << scene->GetFocus() << std::endl;
	}
	if (abkeys[GLFW_KEY_LEFT_CONTROL] && abkeys[GLFW_KEY_LEFT_SHIFT])
	{
		scene->CycleModes();
	}
	if (abkeys[GLFW_KEY_RIGHT_CONTROL] && abkeys[GLFW_KEY_C])
	{
		scene->GenModel("cube.obj");
	}
	InitUI();
	scene->render(*camera);
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
	
	//screen->keyCallbackEvent(key, scancode, action, mode);
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
		
		camera->ScrollProc(static_cast<GLfloat>(yOffset));
		//screen->scrollCallbackEvent(xOffset, yOffset);
}
void MouseCallBack(GLFWwindow * window, double xPos, double yPos)
{
	GLfloat	fxPos = static_cast<GLfloat>(xPos);
	GLfloat	fyPos = static_cast<GLfloat>(yPos);

	if (abkeys[GLFW_KEY_LEFT_SHIFT])
	{
		
		if (bFirstMouse)
		{
			flastX = fxPos;
			flastY = fyPos;
			bFirstMouse = false;
		}
		GLfloat xOffset = fxPos - flastX;
		GLfloat yOffset = flastY - fyPos;

		

		camera->MouseProc(xOffset, yOffset);
	}
	flastX = fxPos;
	flastY = fyPos;
	
}

void DoMovement()
{
	if (abkeys[GLFW_KEY_LEFT_SHIFT])
	{
		
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
	glm::normalize(ray_world);
	//std::cout<< ray_world.x <<ray_world.y<<ray_world.z<< std::endl;
	return ray_world;
}

void Window::onCLick()
{
	if (abkeys[GLFW_MOUSE_BUTTON_1])
	{
		if (scene->GetMode() == 0)
		{
			ObjectPicker(getRay());
		}
	}
}

void Window::ObjectPicker(glm::vec3 rayHit)
{
	//Make bounding sphere
	//glm::vec3 bsCentre = glm::vec3(scene->m_Objects[0]->)
	//sheck points along sphere and points along ray
	//if 
	
	

}
void Window::FacePicker(glm::vec3 rayHit)
{

}
#pragma endregion



