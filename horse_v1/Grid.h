#ifndef GRID_H
#define GRID_H
#include <vector>

// return vertices for a grid 100x100
std::vector<glm::vec3> getGrid();

// return index for the triangles of the grid
GLuint getElements();
#endif
