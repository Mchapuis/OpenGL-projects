#pragma once
#include <vector>
#include <glm.hpp>

//#include <glfw/glfw3.hpp>

class Light
{

protected:
	glm::vec3 light_position;
	glm::vec3 light_color;
public:
	Light();
	glm::vec3 getLightPos(){ return light_position; };
	void setLightPos(double x = 0, double y = 0, double z = 0 );

};