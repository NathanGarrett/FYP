#pragma once
#include <Project\VBOPrimitive.h>

class CylinderPimitive : public VBOPrimitive
{
public:
	CylinderPimitive();
	~CylinderPimitive();
	virtual void render() override;
	virtual void onSelect() override;
private:

};
