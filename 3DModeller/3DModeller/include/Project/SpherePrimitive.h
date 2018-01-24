#pragma once
#include <Project\VBOPrimitive.h>

class SpherePrimitive : public VBOPrimitive
{
public:
	SpherePrimitive();
	~SpherePrimitive();
	virtual void render() override;
	virtual void onSelect() override;
private:

};
