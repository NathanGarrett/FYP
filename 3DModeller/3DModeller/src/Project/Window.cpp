#include <Project/Window.h>

#include <ASSIMP\Exporter.hpp>


Camera* camera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));
GLfloat flastX = 1280 / 2.0f;
GLfloat flastY = 720 / 2.0f;

GLfloat fDeltaTime = 0.0f;
GLfloat lastframe = 0.0f;
bool isClick = false;
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
		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
		{
			isClick = true;
		}
			
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
		//camera->ScrollProc(static_cast<GLfloat>(static_cast<GLfloat>(y)));
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
	
	guiImporterExporter = new nanogui::FormHelper(screen);
	guiToolbar = new nanogui::FormHelper(screen);
	guiTransform = new nanogui::FormHelper(screen);
	guiTransformWindow = guiTransform->addWindow(Eigen::Vector2i(10, 10), "Transform");
	guiToolbarWindow =   guiToolbar->addWindow(Eigen::Vector2i(10, 10), "Tools");
	guiImporterExporterWindow = guiImporterExporter->addWindow(Eigen::Vector2i(10, 10), "File IO");

	indices.resize(3);

	Assimp::Exporter e;
	size_t count = e.GetExportFormatCount();
	for (int i = 0; i < count; i++)
	{
		std::cout << e.GetExportFormatDescription(i)->id << endl;
		std::cout << e.GetExportFormatDescription(i)->fileExtension << endl;
		std::cout << e.GetExportFormatDescription(i)->description << endl;
	}
}

void Window::InitUI()
{
	
	if (!m_bGUIActive)
	{
		//Transform
		guiTransform->addGroup("Scale");
		guiTransform->addVariable("X", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_scale.x, true);
		guiTransform->addVariable("Y", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_scale.y,true);
		guiTransform->addVariable("Z", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_scale.z,true);
		guiTransform->addGroup("Position");
		guiTransform->addVariable("X", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_position.x,true);
		guiTransform->addVariable("Y", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_position.y,true);
		guiTransform->addVariable("Z", scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->m_position.z,true);
		guiTransform->addGroup("Rotation");
		//guiTransform->addButton("Roll", [&]() { scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->roll(1.f); });
		//guiTransform->addButton("Pitch", [&]() { scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->pitch(1.f); });
		//guiTransform->addButton("Yaw", [&]() { scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->yaw(1.f); });
	
		//Tools
		guiToolbar->addGroup("Primitives");
		guiToolbar->addButton("Spawn Cube",			[&]() { scene->GenModel("cube.obj"); })->setTooltip("Spawn a cube");
		guiToolbar->addButton("Spawn Cylinder",		[&]() { scene->GenModel("cylinder.obj"); })->setTooltip("Spawn a cyliner");
		guiToolbar->addButton("Spawn Sphere",		[&]() { scene->GenModel("sphere.obj"); })->setTooltip("Spawn a sphere");
		guiToolbar->addGroup("Selection Mode");
		guiToolbar->addGroup("Mirror Geometry");
		guiToolbar->addButton("Mirror XY", [&]() { command.MirrorGeometryXY(&scene->m_Objects[scene->GetFocus()]->getComponent<ModelComponent>()->getModel(), 1.0f); });
		guiToolbar->addButton("Mirror YZ", [&]() { command.MirrorGeometryYZ(&scene->m_Objects[scene->GetFocus()]->getComponent<ModelComponent>()->getModel(), 1.0f); });
		guiToolbar->addButton("Mirror ZX", [&]() { command.MirrorGeometryZX(&scene->m_Objects[scene->GetFocus()]->getComponent<ModelComponent>()->getModel(), 1.0f); });
		guiToolbar->addGroup("Extrude");
		guiToolbar->addButton("Extrude", [&]() { command.ExtrudeFace(&scene->m_Objects[scene->GetFocus()]->getComponent<ModelComponent>()->getModel(),indices[0],indices[1],indices[2],glm::vec3(0,0,1)); });
		guiToolbar->addGroup("Bevel Edge");
		//File IO
		guiImporterExporter->addGroup("Import a model from folder");
		guiImporterExporter->addVariable("File Name: ", sfileName, true)->setDefaultValue("cube.obj");
		guiImporterExporter->addButton("Import", [&]() {scene->GenModel(sfileName);} );
		guiImporterExporter->addGroup("Export selected model");
		guiImporterExporter->addButton("Export", [&]() {PrepModel(); });
		guiImporterExporter->addGroup("Util");
		guiImporterExporter->addButton("Destroy Selected", [&]() {scene->DestroyModel(); });

		m_bGUIActive = true;
		screen->updateFocus(guiTransformWindow);
		screen->setVisible(true);
		guiTransformWindow->setPosition(nanogui::Vector2i(10, 10));
		screen->performLayout();
		
	}
	
	
	
	
	guiTransform->refresh();
	
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
		onCLick();
		DoMovement();
		glDisable(GL_DEPTH_TEST);
		screen->drawWidgets();
		screen->drawContents();
		glEnable(GL_DEPTH_TEST);
		Render();

		// swap buffers i.e. draw to screen
		glfwSwapBuffers(window);
		
		onCLick();
		
	}
}

void Window::Render()
{
	if (scene->m_Objects.size() < 1) 
	{ 
		scene->GenModel("cube.obj");
		std::cout << scene->m_Objects[0]->getComponent<ModelComponent>()->getModel().getMesh()[0].vertices.size() << std::endl;
	}
	if (abkeys[GLFW_KEY_M])
	{
		std::cout << "M key" << std::endl;
//		command.ExtrudeFace(&scene->m_Objects[scene->GetFocus()]->getComponent<ModelComponent>()->getModel(), glm::vec3(1,0,0));
		//scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->translate(1, 0, 0);

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

void Window::PrepModel()
{
	command.CommitTransform(&scene->m_Objects[scene->GetFocus()]->getComponent<ModelComponent>()->getModel(), scene->m_Objects[scene->GetFocus()]->getComponent<TransformComponent>()->getModelMatrix());
	scene->ExportModel();
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

glm::vec3 Window::getRayVector()
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
	return ray_world;//ray vector
}



glm::vec3 Window::getRayOrigin()
{
	//step one get viewport co-ords
	glm::vec2 clickPos(flastX, flastY);
	glm::vec3 WorldClickPos;
	//step two 3d normalised device co-ords
	WorldClickPos.x = (2.0f * clickPos.x) / m_kiWidth - 1.0f;
	WorldClickPos.y = 1.0f - (2.0f * clickPos.y) / m_kiHeight;
	WorldClickPos.z = 1.0f;
	return WorldClickPos;
}

void Window::onCLick()
{
	if (isClick) 
	{
		Picker(getRayVector(),getRayOrigin());
		isClick = false;
	}
	else return;
}





void Window::Picker(glm::vec3 rayVector,glm::vec3 rayOrigin)
{
	glm::vec3 intersectionPoint;
	Triangle t;
	for (int k = 0; k < scene->m_Objects.size(); k++) //loop through each model
	{	
		size_t imax = scene->m_Objects[k]->getComponent<ModelComponent>()->getModel().getMesh().size();
		for (int i = 0; i < imax; i++) //loop through each mesh in each model
		{
			size_t jmax = scene->m_Objects[k]->getComponent<ModelComponent>()->getModel().getMesh()[i].vertices.size()/3;
			trunc(jmax);
			for (int j = 0; j < jmax; j++) //loop through each tri in each mesh.
			{
				
					t.vertA = scene->m_Objects[k]->getComponent<ModelComponent>()->getModel().getMesh()[0].vertices[0 + (3 * j)].position;
					t.vertB = scene->m_Objects[k]->getComponent<ModelComponent>()->getModel().getMesh()[0].vertices[1 + (3 * j)].position;
					t.vertC = scene->m_Objects[k]->getComponent<ModelComponent>()->getModel().getMesh()[0].vertices[2 + (3 * j)].position;

					if (RayIntersectsTriangle(rayOrigin, rayVector, t, intersectionPoint))
					{
						std::cout << "hit" << std::endl;
						if (scene->GetMode() == 0)//obj mode
						{
							scene->SetFocus(k);

							return;
						}
						if (scene->GetMode() == 1)//face mode
						{
							scene->vertsSelected = true;
							scene->m_vertsSelected[0] = t.vertA;
							scene->m_vertsSelected[1] = t.vertB;
							scene->m_vertsSelected[2] = t.vertC;
							indices[0] = j;
							indices[1] = 1 + (3 * j);
							indices[2] = 2 + (3 * j);

						}
					}
			}	
		}
	}

}

//C++ implementation of the Moller-Trumbore intersection algorithm, from: https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
bool Window::RayIntersectsTriangle(glm::vec3 rayOrigin, glm::vec3 rayVector, Triangle inTriangle, glm::vec3 & outIntersectionPoint)
{
	glm::vec3 edge1, edge2, h, s, q;
	float a, f, u, v;
	edge1 = inTriangle.vertB - inTriangle.vertA;
	edge2 = inTriangle.vertC - inTriangle.vertA;

	h = glm::cross(rayVector, edge2);
	a = glm::dot(h,edge1);
	if (a > -EPSILON && a < EPSILON)
	{
		return false;
	}

	f = 1 / a;
	s = rayOrigin - inTriangle.vertA;
	u = f * (glm::dot(h,s));
	if (u < 0.0 || u > 1.0)
	{
		return false;
	}

	q = glm::cross(s, edge1);
	v = f * (glm::dot(q,rayVector));
	if (v < 0.0 || u + v > 1.0)
	{
		return false;
	}
	//at this point we can calculate t to find the intesection point on the line.
	float t = f * (glm::dot(q,edge2));
	if (t > EPSILON) // ray intersection
	{
		outIntersectionPoint = rayOrigin + rayVector * t;
		return true;
	}
	else //there is a line intersection but no ray intersection
	{
		return false;
	}

}

#pragma endregion