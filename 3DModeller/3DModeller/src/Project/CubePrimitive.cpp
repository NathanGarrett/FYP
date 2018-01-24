#include "Project/CubePrimitive.h"

CubePrimitive::CubePrimitive()
{
	float fvert = 50;
	
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

	glGenBuffers(1, &vaoHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vaoHandle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vaoHandle);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, (void*)0);
}

CubePrimitive::~CubePrimitive()
{
}

void CubePrimitive::render()
{
	glDrawArrays(GL_TRIANGLES, 0,24); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void CubePrimitive::onSelect()
{
}
