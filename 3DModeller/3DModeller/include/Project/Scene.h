#pragma once
#include <Project/Model.h>
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
	
private:
	std::vector<Model*> m_Objects;
	
	int width, height;
	glm::mat4 model = glm::mat4(1.0f); //Model matrix
	void setMatrices(Camera camera); //Set the camera matrices
	void compileAndLinkShader(); //Compile and link the shader
	
	Shader m_ObjectShader;
	Shader m_WireframeShader;
	Shader m_ShadedWireframeShader;

};


