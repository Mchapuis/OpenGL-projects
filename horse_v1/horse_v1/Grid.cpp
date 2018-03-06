#include "stdafx.h"
#include <vector>
//#include <stdio.h>
//#include <cstring>
#include <iostream>
#include <glm.hpp>

#include "Grid.h"

// create vertices for a grid 100X100
std::vector<glm::vec3> getGrid(){
	//int x = -50;
	//int y = -50;
	//std::vector<glm::vec3> v;
	//glm::vec3 temp;
	//for (int i = 0; i < 100; i+=1){

	//	temp = glm::vec3((float)i, 0.0, 0.0);
	//	v.push_back(temp);

	//	temp = glm::vec3((float)i, 1.0, 0.0);
	//	v.push_back(temp);
	//	
	//	temp = glm::vec3(0.0, (float)i, 0.0);
	//	v.push_back(temp);

	//	temp = glm::vec3(1.0, (float)i, 0.0);
	//	v.push_back(temp);
	//}

	std::vector<glm::vec3> v = {
		glm::vec3(0, 0, 0), // bottom-left
		glm::vec3(1, 0, 0), // bottom-right
		glm::vec3(0, 1, 0), // top-left
		glm::vec3(1, 1, 0), // top-right

		//glm::vec3(1, 0, 0), // bottom-left //1
		glm::vec3(2, 1, 0), // bottom-right
		glm::vec3(1, 2, 0), // top-left
		glm::vec3(2, 2, 0) // top-right
	};

	return v;
}

// return index for the grid 100x100
GLuint getElements(){
	GLuint v = 4;
	GLuint elements[] = {
		0, 1, 2,
		1, 2, 3

	};
	return v;
}
