#pragma once
#include <GLAD/glad.h>
class VBOPrimitive
{
public:
	virtual void render() = 0;
	virtual void onSelect() = 0;
};

