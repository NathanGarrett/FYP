#pragma once
#include <VBOPrimitive.h>

class VBOCube : public VBOPrimitive
{
public:
	VBOCube(float fvert);
	~VBOCube();
	void render() override;
private:

};

