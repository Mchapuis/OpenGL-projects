#pragma once
#include <vector>
#include <glm.hpp>

class HorseContainer
{
private:
	struct Node{
		struct Node *children; 
		struct Node *parent;
		int numOfChildren;
		char c;
	};
	Node *current; // current pointer

};