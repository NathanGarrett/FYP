#pragma once

#include <GLM\glm.hpp>
#include <vector>
#include <GLFW\glfw3.h>

struct Mesh
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<GLuint> indices;
};