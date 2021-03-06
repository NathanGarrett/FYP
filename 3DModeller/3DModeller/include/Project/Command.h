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
	void ExtrudeFace(Model *model, int v1, int v2, int v3,int meshIndex,int mode, glm::vec3 mag);
	void CommitTransform(Model* model,glm::mat4 modmat);
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

