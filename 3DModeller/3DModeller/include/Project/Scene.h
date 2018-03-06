#pragma once
#include <Project/ModelComponent.h>
#include <Project/TransformComponent.h>
#include <Project/SceneObject.h>
#include <Project/Camera.h>
#include <Project/Shader.h>
#include <GLM/glm.hpp>
#include <GLFW/glfw3.h>


class Scene
{

public:
	Scene(); //Constructor

	void initScene(Camera camera); //Initialise the scene

	void update(float t); //Update the scene

	void render(Camera camera);	//Render the scene

	void GenModel(std::string model);

	int GetMode() { return m_RenderMode; }
	void CycleModes();

	std::vector<SceneObject*> m_Objects;
	
private:
	
	unsigned int m_RenderMode = 0;
	int width, height;
	glm::mat4 model = glm::mat4(1.0f); //Model matrix
	void setMatrices(Camera camera); //Set the camera matrices
	void compileAndLinkShader(); //Compile and link the shader
	
	Shader Wire;
	Shader Object;
	vector<Shader*> m_shaders;

	
};


