#pragma once
#include <Project\VBOPrimitive.h>

class CylinderPrimitive : public VBOPrimitive
{
public:
	CylinderPrimitive();
	~CylinderPrimitive();
	virtual void render() override;
	virtual void onSelect() override;
private:

};
