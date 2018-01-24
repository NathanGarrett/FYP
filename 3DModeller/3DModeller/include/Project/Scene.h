#pragma once
#include <Project\CubePrimitive.h>
#include <Project/CylinderPrimitive.h>
#include <Project\SpherePrimitive.h>
#include <Project/Camera.h>
#include <Project/Shader.h>
#include <GLM\glm.hpp>
#include <GLFW/glfw3.h>
class Scene
{

public:
	Scene(); //Constructor

	void setLightParams(Camera camera); //Setup the lighting

	void initScene(Camera camera); //Initialise the scene

	void update(float t); //Update the scene

	void render(Camera camera);	//Render the scene

	void resize(Camera camera, int w, int h); //Resize
	void GenPrimitive(std::string type);
	
private:

	Shader m_Default;
	int width, height;

	glm::mat4 model; //Model matrix
	void setMatrices(Camera camera, bool DrawSkyBox); //Set the camera matrices
	void compileAndLinkShader(); //Compile and link the shader

};
};

