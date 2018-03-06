#pragma once
#include "stdafx.h"
#include "Light.h"

using namespace std;

// constructor
Light::Light(){
	light_position = glm::vec3(1, 0, 3);
}

void Light::setLightPos(double x, double y, double z){
	light_position = glm::vec3(x,y,z);
}

glm::vec3 Light::getLightPos(){
	return light_position;
}