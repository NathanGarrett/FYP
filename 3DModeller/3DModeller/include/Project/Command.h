#pragma once
#include <Project\CLHandler.h>
#include <Project\Model.h>
#include <Project\Mesh.h>
#include <ASSIMP/mesh.h>
#include <GLM\glm.hpp>
#include <vector>
#include <iostream>

class Command
{
public:
	Command() {};
	~Command() {};
	void MirrorGeometryXY(Model *model, float zOffset);
	void MirrorGeometryYZ(Model *model, float xOffset);
	void MirrorGeometryZX(Model *model, float yOffset);
	void ExtrudeFace(Model *model, glm::vec3 mag);
	void BevelObject(Model *model, float offset);
private:
	CLHandler handler;

	glm::mat4 reflectXY = 
	{ 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-1, 0,
		0, 0, 0, 1 };

	glm::mat4 reflectYZ = 
	{ -1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-1, 0,
		0, 0, 0, 1 };

	glm::mat4 reflectZX = 
	{ 1,  0, 0, 0,
		0, -1, 0, 0,
		0,  0,  1, 0,
		0, 0, 0, 1 };


};

