#pragma once
#include "Component.h"
#include "Model.h"

class ModelComponent : public Component
{
public:
	ModelComponent(Model* model) : m_Model(model) {};

	void OnUpdate() override
	{
	}

	void OnMessage(const std::string m) override
	{
	}
	Model& getModel() { return *m_Model; };
	void setTextureID(unsigned int id) { m_iTextureID = id; }
	unsigned int getTextureID() const { return m_iTextureID; }
	void Disable() { m_bEnable = false; }
	void Enable() { m_bEnable = true; }
	bool Enabled() { return m_bEnable; }
private:
	bool m_bEnable = true;
	unsigned int m_iTextureID;

	Model* m_Model;
};