#pragma once
#include <Project\CLHandler.h>
#include <Project\Model.h>
#include <Project\Mesh.h>
#include <ASSIMP\postprocess.h>
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

private:
	CLHandler handler;

	glm::mat4 reflectXY = { 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-1, 0,
		0, 0, 0, 1 };

	glm::mat4 reflectYZ = { -1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-1, 0,
		0, 0, 0, 1 };

	glm::mat4 reflectZX = { 1,  0, 0, 0,
		0, -1, 0, 0,
		0,  0,  1, 0,
		0, 0, 0, 1 };
};

