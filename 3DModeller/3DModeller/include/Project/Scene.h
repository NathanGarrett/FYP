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

	int GetFocus() { return m_Focus; }
	void SetFocus(int focus);
	void CycleFoci();

	std::vector<SceneObject*> m_Objects;
	
private:
	
	unsigned int m_RenderMode = 0;
	unsigned int m_Focus = 0;
	int width, height;
	void setMatrices(Camera camera, unsigned int i); //Set the camera matrices
	void compileAndLinkShader(); //Compile and link the shader
	
	Shader Wire;
	Shader Object;
	vector<Shader*> m_shaders;

	
};


