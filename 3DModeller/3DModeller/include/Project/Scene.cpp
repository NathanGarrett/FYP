#include "Scene.h"

Scene::Scene()
{
}

void Scene::setLightParams(Camera camera)
{
	glm::vec3 worldLight = glm::vec3(10, 10, 10);
}

void Scene::initScene(Camera camera)
{
	glEnable(GL_DEPTH_TEST);
	setLightParams(camera);

	compileAndLinkShader();
}

void Scene::update(float t)
{

}

void Scene::render(Camera camera)
{
	
}



void Scene::GenPrimitive(std::string type)
{
}

void Scene::setMatrices(Camera camera, bool DrawSkyBox)
{
}

void Scene::compileAndLinkShader()
{
}
