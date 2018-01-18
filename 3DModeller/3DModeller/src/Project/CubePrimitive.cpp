#include "Project/CubePrimitive.h"

CubePrimitive::CubePrimitive()
{
	float fvert = 50;
	faces = 6;
	float v[] =
	{
		-fvert,-fvert,fvert,  //v0
		fvert,-fvert,fvert,  //v1
		fvert,fvert,fvert,  //v2
		-fvert,fvert,fvert, //v3

		-fvert,-fvert,-fvert, //v4
		fvert,-fvert,-fvert, //v5
		fvert,fvert,-fvert, //v6
		-fvert,fvert,-fvert //v7
	}; //vertex array

	indices =
	{
		//front
		0,1,2,
		2,3,0,
		//top
		1,5,6,
		6,2,1,
		//back
		7,6,5,
		5,4,7,
		//bottom
		4,0,3,
		3,7,4,
		//left
		4,5,1,
		1,0,4,
		//right
		3,2,6,
		6,7,3
	};


	glGenVertexArrays(1, &boxVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(boxVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(v), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



}

CubePrimitive::~CubePrimitive()
{
}

void CubePrimitive::render()
{
	glBindVertexArray(vaoHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle[1]);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}

void CubePrimitive::onSelect()
{
}
