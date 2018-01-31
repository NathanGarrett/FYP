#include "Project/Scene.h"

Scene::Scene()
{
	
}

void Scene::setLightParams(Camera camera)
{
	glm::vec3 worldLight = glm::vec3(10, 10, 10);
}

void Scene::initScene(Camera camera)
{
	
	Bitmap diffbmp = Bitmap::bitmapFromFile("textures/ogre_diffuse.png");
	diffbmp.flipVertically();
	m_defaultTexture = new Texture(diffbmp);
	Bitmap normbmp = Bitmap::bitmapFromFile("textures/ogre_normalmap.png");
	normbmp.flipVertically();
	m_defaultNormalMap = new Texture(normbmp);
	
	setLightParams(camera);
	compileAndLinkShader();
	setMatrices(camera);

	glEnable(GL_DEPTH_TEST);

	
	
}

void Scene::update(float t)
{
	
}

void Scene::render(Camera camera)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_DefaultShader.use();
		m_Objects[i]->render();
	}
}



void Scene::setMatrices(Camera camera)
{
	m_DefaultShader.setUniform("Model", model);
	m_DefaultShader.setUniform("View", camera.GetViewMatrix());
	m_DefaultShader.setUniform("Projection", camera.GetProjectionMatrix());

	m_DefaultShader.setUniform("lightPos", glm::vec3(0, 0, 10));
	m_DefaultShader.setUniform("viewPos", camera.GetCamPos());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_defaultTexture->object());
	m_DefaultShader.setUniform("diffusemap", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_defaultNormalMap->object());
	m_DefaultShader.setUniform("normalmap", 1);
}

void Scene::compileAndLinkShader()
{
	m_DefaultShader.compileShader("res/normalShader.vert");
	m_DefaultShader.compileShader("res/normalShader.frag");
	m_DefaultShader.link();
	m_DefaultShader.validate();
	
}

void Scene::GenModel(std::string model)
{
	VBOMesh* temp = new VBOMesh(("models/" + model).c_str(), false, true, true);
	m_Objects.push_back(temp);
}
