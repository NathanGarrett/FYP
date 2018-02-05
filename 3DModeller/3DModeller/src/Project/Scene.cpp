#include "Project/Scene.h"

Scene::Scene()
{
	
}



void Scene::initScene(Camera camera)
{
	
	compileAndLinkShader();
	//glEnable(GL_DEPTH_TEST);

}

void Scene::update(float t)
{
	
}

void Scene::render(Camera camera)
{
	m_ObjectShader.use();
	//Object Shader light uniforms
	m_ObjectShader.setUniform("lightPos", glm::vec3(0, 0, 0));
	m_ObjectShader.setUniform("La", glm::vec3(0.75, 0.5, 0.5));
	m_ObjectShader.setUniform("Ld", glm::vec3(0.75, 0.5, 0.5));
	m_ObjectShader.setUniform("Ls", glm::vec3(0.75, 0.5, 0.5));
	//Object shader material uniforms
	m_ObjectShader.setUniform("Ka", glm::vec3(0.5,0.5,0.5));
	m_ObjectShader.setUniform("Kd", glm::vec3(0.5, 0.5, 0.5));
	m_ObjectShader.setUniform("Ks", glm::vec3(0.5, 0.5, 0.5));


	for (int i = 0; i < m_Objects.size(); i++)
	{
		setMatrices(camera);
		
		m_Objects[i]->render();
		
	}
	
}



void Scene::setMatrices(Camera camera)
{
	glm::mat4 ModelView = camera.GetViewMatrix() * model;
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ModelView));
	m_ObjectShader.setUniform("M", model);
	m_ObjectShader.setUniform("V", camera.GetViewMatrix());
	m_ObjectShader.setUniform("P", camera.GetProjectionMatrix());
	m_ObjectShader.setUniform("NormalMatrix", NormalMatrix);
}

void Scene::compileAndLinkShader()
{
	m_ObjectShader.compileShader("res/ObjectShader.vert");
	m_ObjectShader.compileShader("res/ObjectShader.frag");
	//m_DefaultShader.compileShader("res/wireframeShader.geom");

	m_ObjectShader.link();
	m_ObjectShader.validate();
	
}

void Scene::GenModel(std::string model)
{
	VBOMesh* temp = new VBOMesh(("models/" + model).c_str(), false, true, true);
	m_Objects.push_back(temp);
}
