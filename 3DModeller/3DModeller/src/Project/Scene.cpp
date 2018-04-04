#include "Project/Scene.h"

Scene::Scene()
{
	
}



void Scene::initScene(Camera camera)
{
	m_shaders.reserve(2);
	compileAndLinkShader();
    glEnable(GL_DEPTH_TEST);
}

void Scene::update(float t)
{
	
}

void Scene::render(Camera camera)
{
	m_shaders[m_RenderMode]->use();
	//Object Shader light uniforms
	m_shaders[m_RenderMode]->setUniform("LightPosition", glm::vec3(10, 10, 10));
	m_shaders[m_RenderMode]->setUniform("La", glm::vec3(1.0, 1.0, 1.0));
	m_shaders[m_RenderMode]->setUniform("Ld", glm::vec3(1.0, 1.0, 1.0));
	m_shaders[m_RenderMode]->setUniform("Ls", glm::vec3(1.0, 1.0, 1.0));
	
	//Line Info	
	m_shaders[m_RenderMode]->setUniform("Line.Width", 0.0001f);
	m_shaders[m_RenderMode]->setUniform("Line.Color", glm::vec4(1.0, 1.0, 1.0, 1.0));

	
	
	for (unsigned int i = 0; i < m_Objects.size(); i++)
	{
		
		if (i == m_Focus)
		{
			//Object shader material uniforms
			m_shaders[m_RenderMode]->setUniform("Ka", glm::vec3(1.0, 0.0, 0.0));
			m_shaders[m_RenderMode]->setUniform("Kd", glm::vec3(1.0, 0.0, 0.0));
			m_shaders[m_RenderMode]->setUniform("Ks", glm::vec3(1.0, 0.0, 0.0));
		}
		else 
		{
			//Object shader material uniforms
			m_shaders[m_RenderMode]->setUniform("Ka", glm::vec3(1.0, 0.5, 0.0));
			m_shaders[m_RenderMode]->setUniform("Kd", glm::vec3(1.0, 0.5, 0.0));
			m_shaders[m_RenderMode]->setUniform("Ks", glm::vec3(1.0, 0.5, 0.0));

		}
		setMatrices(camera, i); //update shaders with new camera and model matrices for each object i
		m_Objects[i]->getComponent<ModelComponent>()->getModel().render(m_shaders[m_RenderMode]->getHandle());
		//m_Objects[i]->getComponent<ModelComponent>()->getModel().getMesh()[0].vertices[i].position;
	}
}



void Scene::setMatrices(Camera camera, unsigned int i)
{
	glm::mat4 model = m_Objects[i]->getComponent<TransformComponent>()->getModelMatrix();
	glm::mat4 View = camera.GetViewMatrix();
	glm::mat4 Projection = camera.GetProjectionMatrix();
	glm::mat4 ModelView = camera.GetViewMatrix() * model;
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(ModelView));
	glm::mat4 MVP = Projection * View * model;

	//glm::mat4 ViewPortMatrix;
	m_shaders[m_RenderMode]->setUniform("Model", model);
	m_shaders[m_RenderMode]->setUniform("View", View);
	m_shaders[m_RenderMode]->setUniform("Projection", Projection);
	m_shaders[m_RenderMode]->setUniform("MVP", MVP);
	m_shaders[m_RenderMode]->setUniform("NormalMatrix", NormalMatrix);
	
}

void Scene::compileAndLinkShader()
{
	
	//Object set up
	Object.compileShader("res/ObjectShader.vert");
	Object.compileShader("res/ObjectShader.frag");
	Object.link();
	Object.validate();
	//Wireframe set up
	Wire.compileShader("res/WireframeShader.vert");
	Wire.compileShader("res/WireframeShader.geom");
	Wire.compileShader("res/WireframeShader.frag");
	Wire.link();
	Wire.validate();
	m_shaders.push_back(&Object);
	m_shaders.push_back(&Wire);
}

void Scene::GenModel(std::string model)
{
	Model* temp = new Model(("models/" + model).c_str());
	SceneObject* tempSO = new SceneObject();
	tempSO->addComponent(new ModelComponent(temp));
	tempSO->addComponent(new TransformComponent(glm::vec3(0, 0, 0), glm::quat(0, 0, 0, 0), glm::vec3(1, 1, 1)));
	m_Objects.push_back(tempSO);

}


void Scene::CycleModes()
{
	if (m_RenderMode < m_shaders.size()-1)
	{
		m_RenderMode++; 
	}
	else if (m_RenderMode == m_shaders.size()-1)
	{
		m_RenderMode = 0;
	}
}

void Scene::CycleFoci()
{
	if (m_Focus < m_Objects.size() - 1)
	{
		m_Focus++;
	}
	else if (m_Focus == m_Objects.size() - 1)
	{
		m_Focus = 0;
	}
}
