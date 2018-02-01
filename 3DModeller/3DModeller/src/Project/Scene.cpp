#include "Project/Scene.h"

Scene::Scene()
{
	
}



void Scene::initScene(Camera camera)
{
	
	compileAndLinkShader();
	glEnable(GL_DEPTH_TEST);
	
	//compileAndLinkShader();
	

	Bitmap diffbmp = Bitmap::bitmapFromFile("textures/rantex.png");
	diffbmp.flipVertically();
	m_defaultTexture = new Texture(diffbmp);
	Bitmap normbmp = Bitmap::bitmapFromFile("textures/ogre_normalmap.png");
	normbmp.flipVertically();
	m_defaultNormalMap = new Texture(normbmp);

}

void Scene::update(float t)
{
	
}

void Scene::render(Camera camera)
{
	m_DefaultShader.use();

	m_DefaultShader.setUniform("lightPos", glm::vec3(0, 0, 10));
	m_DefaultShader.setUniform("viewPos", camera.GetCamPos());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_defaultTexture->object());
	m_DefaultShader.setUniform("diffusemap", 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_defaultNormalMap->object());
	m_DefaultShader.setUniform("normalmap", 1);

	

	for (int i = 0; i < m_Objects.size(); i++)
	{
		setMatrices(camera);
		
		m_Objects[i]->render();
		
	}
	
}



void Scene::setMatrices(Camera camera)
{
	m_DefaultShader.setUniform("Model", model);
	m_DefaultShader.setUniform("View", camera.GetViewMatrix());
	m_DefaultShader.setUniform("Projection", camera.GetProjectionMatrix());
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
