#pragma once

#include <string>

class Component
{
public:
	virtual void OnUpdate() = 0;
	virtual void OnMessage(const std::string m) = 0;

};