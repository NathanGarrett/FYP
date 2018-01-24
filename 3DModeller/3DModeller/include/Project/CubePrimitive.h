#pragma once
#include "VBOPrimitive.h"
#include <vector>
class CubePrimitive : public VBOPrimitive
{
public:
	CubePrimitive();
	~CubePrimitive();
	virtual void render() override;
	virtual void onSelect() override;
private:
	unsigned int vaoHandle; //pos of vao
	
};

