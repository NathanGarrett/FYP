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
	m_ObjectShader.setUniform("LightPosition", glm::vec3(10, 10, 10));
	m_ObjectShader.setUniform("La", glm::vec3(0.0, 0.0, 0.0));
	m_ObjectShader.setUniform("Ld", glm::vec3(0.0, 0.0, 0.0));
	m_ObjectShader.setUniform("Ls", glm::vec3(0.0, 0.0, 0.0));
	//Object shader material uniforms
	m_ObjectShader.setUniform("Ka", glm::vec3(0.0,0.0,0.0));
	m_ObjectShader.setUniform("Kd", glm::vec3(0.0,0.0,0.0));
	m_ObjectShader.setUniform("Ks", glm::vec3(0.0,0.0,0.0));
	//Line Info
	m_ObjectShader.setUniform("Line.Width", 0.1f);
	m_ObjectShader.setUniform("Line.Color", glm::vec4(1.0, 1.0, 1.0, 1.0));

	for (int i = 0; i < m_Objects.size(); i++)
	{
		setMatrices(camera);
		
		m_Objects[i]->render();
		
	}
	
}



void Scene::setMatrices(Camera camera)
{
	glm::mat4 View = camera.GetViewMatrix();
	glm::mat4 Projection = camera.GetProjectionMatrix();
	glm::mat4 ModelView = camera.GetViewMatrix() * model;
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ModelView));
	glm::mat4 MVP = Projection * View * model;

	//glm::mat4 ViewPortMatrix;

	m_ObjectShader.setUniform("Model", model);
	m_ObjectShader.setUniform("View", View);
	m_ObjectShader.setUniform("Projection", Projection);
	m_ObjectShader.setUniform("MVP", MVP);
	m_ObjectShader.setUniform("NormalMatrix", NormalMatrix);

}

void Scene::compileAndLinkShader()
{
	m_ObjectShader.compileShader("res/WireframeShader.vert");
	m_ObjectShader.compileShader("res/WireframeShader.geom");
	m_ObjectShader.compileShader("res/WireframeShader.frag");
	

	m_ObjectShader.link();
	m_ObjectShader.validate();
	
}

void Scene::GenModel(std::string model)
{
	VBOMesh* temp = new VBOMesh(("models/" + model).c_str(), false, false, false);
	m_Objects.push_back(temp);
}
