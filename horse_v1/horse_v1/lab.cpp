#pragma once
#include "stdafx.h"
/*
#ifndef STDAFX_H
#define STDAFX_H
*/
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>

#include <chrono>
#include "objloader.h"



//----------------- VIEW MATRIX
glm::vec3 camera_pos = glm::vec3(0.0, 30.0, 40.5); // -10 at z(2.2, 60.0, 50.5)
glm::vec3 camera_tar = glm::normalize(glm::vec3(0, 0, 1)); // or direction...need to be normalized!
glm::vec3 camera_up = glm::vec3(0, 2, 0);// up in the y position
glm::mat4 view_matrix;

//---------------- MODEL MATRIX

glm::mat4 model_matrix = glm::mat4(1.0f); // identity  --- this will be used for scale, transform and rotation
glm::mat4 grid_matrix = glm::mat4(1.0f);
glm::mat4 coord_matrix = glm::mat4(1.0f);
glm::mat4 horse_model_matrix = glm::mat4(1.0f);
glm::mat4 scale = glm::mat4(1.0f);
glm::mat4 trans = glm::mat4(1.0f);
glm::mat4 rotat = glm::mat4(1.0f);

//------------------TRANSFORM MATRIX
glm::mat4 _trans = glm::mat4(1.0f);
glm::mat4 _rotat = glm::mat4(1.0f);
glm::mat4 _scale = glm::mat4(1.0f);


//------------------ To translate horse with space bar
int coordX = 0;
int coordY = 0;
int coordZ = 0;

//------------------SHADER POINTERS;
GLuint model_addr;
GLuint grid_addr;
GLuint coord_addr;
GLuint camera_addr;
GLuint pers_addr;

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 800;
GLFWwindow* window;


void inputHorseTranslate(){
	int max = 50;
	int min = -50;
	coordX = rand() % (max - min + 1) + min;
	coordZ = rand() % (max - min + 1) + min;
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(coordX, 0, coordZ));
	model_matrix = glm::mat4(1.0f);
	model_matrix *= trans;
}

void inputHorseScaleUp(){
	_scale = glm::scale(glm::mat4(1.0f),glm::vec3(1.01, 1.01, 1.01));
	model_matrix *= _scale;
}
void inputHorseScaleDown(){
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05, 0.05, 0.05));
	model_matrix = _scale;
}
void inputHorseMoveLeft(){
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(-5, 0, 0));
	//model_matrix = glm::mat4(1.0f);
	model_matrix *= trans;

}
void inputHorseMoveRight(){
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(5, 0, 0));
	//model_matrix = glm::mat4(1.0f);
	model_matrix *= trans;
}
void inputHorseMoveUp(){
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 5));
	//model_matrix = glm::mat4(1.0f);
	model_matrix *= trans;
}
void inputHorseMoveDown(){
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5));
	//model_matrix = glm::mat4(1.0f);
	model_matrix *= trans;
}
void inputHorseRotateLeft(){
	// center object before rotation
	model_matrix *= glm::mat4(1.0f);
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(-10.f), glm::vec3(0, -1, 0));
	model_matrix *= _rotat;
}
void inputHorseRotateRight(){
	// center object before rotation
	model_matrix *= glm::mat4(1.0f);
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(0, 1, 0));
	model_matrix *= _rotat;
}
void inputHorseRotateUp(){
	model_matrix *= glm::mat4(1.0f);
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(10.f), glm::vec3(0, 0, 1));
	model_matrix *= _rotat;
}
void inputHorseRotateDown(){
	model_matrix *= glm::mat4(1.0f);
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(-10.f), glm::vec3(0, 0, 1));
	model_matrix *= _rotat;
}
////////////////////////////////////////////////////
//                HORSE SETUP
////////////////////////////////////////////////////

void setMatrix(){
	// center object before rotation
	model_matrix *= glm::mat4(1.0f);
	model_matrix *= _rotat;
	model_matrix *= _trans;
	model_matrix *= _scale;
}
void setHeadMatrix(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(-35.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 16, 0));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(3, 1, 1));

	// center object before rotation
	model_matrix *= glm::mat4(1.0f);
	model_matrix *= _rotat;
	model_matrix *= _trans;
	model_matrix *= _scale;

}




void setTorso(){
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, 10, 0));
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(-1, 0, 0));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(5, 2, 2));
	model_matrix *= _trans;
	model_matrix *= _scale;
}

void setNeck(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(25.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-10, 9, 0));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(3, 1, 0.8));
	setMatrix();
	//printf("neck!");
}
void setUpperLeg1(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(4, 7, 1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 2, 0.5));
	setMatrix();

}
void setUpperLeg2(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(4, 7, -1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 2, 0.5));
	setMatrix();
}
void setLowerLeg1(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(4, 3, 1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 2, 0.5));
	setMatrix();
}
void setLowerLeg2(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(4, 3, -1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 2, 0.5));
	setMatrix();
}
void setUpperArm1(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-4, 7, 1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 2, 0.5));
	setMatrix();
}
void setUpperArm2(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-4, 7, -1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 2, 0.5));
	setMatrix();
}
void setLowerArm1(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-4, 3, 1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 2, 0.5));
	setMatrix();
}
void setLowerArm2(){
	_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-4, 3, -1));
	_scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 2, 0.5));
	setMatrix();
}

// For the View
void update_view(){
	view_matrix = glm::lookAt(
		camera_pos,  camera_tar, camera_up);// 
}

// called each time a key is pressed
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	//std::cout << key << std::endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	
	if (key == GLFW_KEY_UP ){
		camera_pos.z += 1;
		update_view();
	}
	
	if (key == GLFW_KEY_DOWN ){
		camera_pos.z -= 1;
		update_view();
	}
	
	if (key == GLFW_KEY_SPACE ){
		inputHorseTranslate();
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
	}

	if (key == GLFW_KEY_U){
		inputHorseScaleUp();
	}
	if (key == GLFW_KEY_J){
		inputHorseScaleDown(); 
	}
	if (key == GLFW_KEY_A && mods == GLFW_MOD_SHIFT){
		inputHorseMoveLeft();
	}
	if (key == GLFW_KEY_D && mods == GLFW_MOD_SHIFT){
		inputHorseMoveLeft();
	}
	if (key == GLFW_KEY_W && mods == GLFW_MOD_SHIFT){
		inputHorseMoveUp();
	}
	if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT){
		inputHorseMoveDown();
	}
	if (key == GLFW_KEY_A && mods != GLFW_MOD_SHIFT){ // rotate left
		inputHorseRotateLeft();
	}
	if (key == GLFW_KEY_D && mods != GLFW_MOD_SHIFT){ // rotate right 1 grid
		inputHorseRotateLeft();
	}
	if (key == GLFW_KEY_W && mods != GLFW_MOD_SHIFT){ // rotate up
		inputHorseRotateUp();
	}
	if (key == GLFW_KEY_S && mods != GLFW_MOD_SHIFT){ // rotate down
		inputHorseRotateDown();
	}
	if (key == GLFW_KEY_P){
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	if (key == GLFW_KEY_L){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
	}
	if (key == GLFW_KEY_T){
		glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);

	}
	
}

	//////////////////////////////
	// SHADER
	/////////////////////////////
GLuint loadShader(std::string vertex_shader_path, std::string fragment_shader_path) {

	// Create the shader
	// note: to delete shader, use glDeleteShader..
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER); // create a shader object --- gl_vertex_shader intended to run on the programmable vertex processor
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);// -- gl_fragment same as above but for fragment processor

	if (VertexShaderID == 0 || FragmentShaderID == 0){
		/*error!*/
		printf("shader problem! was not initialized correctly");
	}

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode; // will get all from vertexShaderStream
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in); // ------------? only reading the string ?

	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);

	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", fragment_shader_path.c_str());
		getchar();
		exit(-1);
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_shader_path.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();

	// send information about the shader: ID, # of lines in &reference, the &reference, length --set to NULL for now..
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	
	// compiler with shader id
	glCompileShader(VertexShaderID);

	// Check Vertex Shader for errors
	// arg: ID, type of status requested, status code returned

	// Result is GL_FALSE if there is a problem
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);

	// InfoLogLength return the log of the problem
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_shader_path.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();

	// note:do update shader, need to call glDetachShader first
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

	// associate a generic vertex attribute index with a named attribute variable
	glBindAttribLocation(ProgramID, 0, "in_Position");// ----- ?


	// linking vertex and fragment shader together
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID); //free up memory
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}


int init() {
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

	// Init GLFW library
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Lab", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// input
	glfwSetKeyCallback(window, key_callback);


	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}


int main()
{

	if (init() < 0) {
		return -1;
	}

	GLuint shaderProgram = loadShader("vertex.shader", "fragment.shader");

	glUseProgram(shaderProgram);

	// grid
	std::vector<glm::vec3> v;
	std::vector<glm::vec3> nv;
	std::vector<glm::vec2> uv;

	// square for the horse
	std::vector<glm::vec3> s;
	std::vector<glm::vec3> sv;
	std::vector<glm::vec2> suv;

	// load objects
	loadOBJ("grid2.obj", v, nv, uv);
	loadOBJ("square3.obj", s, sv, suv);

	// -------------- X, Y, Z COORDINATES
	// Red X line, Green Y line, Bleu Z line
	// 5 subdivision == 15.625
	GLfloat coord[] =
	{
		0.0, 0.0, 0.0, 1.0, 0.0, 0.0,
		18.0, 0.0, 0.0, 1.0, 0.0, 0.0,

		0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
		0.0, 18.0, 0.0, 0.0, 1.0, 0.0,

		0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
		0.0, 0.0, 18.0, 0.0, 0.0, 1.0
	};
	// --------------------------------------
	// ------------- X, Y, Z COORDINATES
	// ---------------------------------------
	GLuint coord_VBO, coord_VAO;

	glGenVertexArrays(1, &coord_VAO); // the VertexBufferID
	glBindVertexArray(coord_VAO);

	glGenBuffers(1, &coord_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, coord_VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(coord),coord,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// -----------------------------------
	// ------------- GRID
	// -----------------------------------

	GLuint grid_VBO, grid_VAO; // unsigned integer for opengl

	glGenVertexArrays(1, &grid_VAO); // the VertexBufferID
	glBindVertexArray(grid_VAO);

	glGenBuffers(1, &grid_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, grid_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*v.size(), &v[0], GL_STATIC_DRAW);//  sizeof(glm::vec3)*s.size() + 
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3)*v.size(), &v[0]);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*v.size(), sizeof(glm::vec3)*s.size(), &s[0]);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// for nice colors on a triangle
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);


	// ---------------------------------
	// ------------- SQUARE
	// --------------------------------
	GLfloat square_vertex_color[] = {
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0,
		255.0, 0.0, 0.0
	};
	GLuint square_VBO, square_VAO;
	glGenVertexArrays(1, &square_VAO);
	glBindVertexArray(square_VAO);

	glGenBuffers(1, &square_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, square_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*s.size(), 0, GL_STATIC_DRAW);//&s[0]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3)*s.size(), &s[0]);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*s.size(), sizeof(square_vertex_color), square_vertex_color);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), 0);//(GLvoid *)(3 * sizeof(GLfloat))
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//----------------- GRID
	glm::mat4 grid = glm::mat4(1.0f);
	
	//----------------- PROJECTION MATRIX
	//45 is the FOV, fraction is the aspect ratio, never put zero, calculate only after/before in z
	glm::mat4 perspective = glm::perspective(glm::radians(90.0f), 8.0f / 6.0f, 0.1f, 150.0f);

	// model addresse referenced in vertex shader... we know where to send information
	//-------------------FOR THE SHADER PROGRAM
	model_addr = glGetUniformLocation( // returns an integer that represents the location of a specific uniform variable within a program object
		shaderProgram, "m_matrix");
	grid_addr = glGetUniformLocation( // returns an integer that represents the location of a specific uniform variable within a program object
		shaderProgram, "m_matrix");
	coord_addr = glGetUniformLocation( // returns an integer that represents the location of a specific uniform variable within a program object
		shaderProgram, "m_matrix");
	camera_addr = glGetUniformLocation(
		shaderProgram, "view_matrix");
	pers_addr = glGetUniformLocation(
		shaderProgram, "p_matrix");
	
	// --------------------BACKGROUND COLOR
	// red, green, blue, alpha
	glClearColor(0.7f, 0.7f, 0.7f, 1);

	// -----------------MODEL MATRIX ------------------------
	
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(40, 40, 40)); // so now the identity matrix is .5 instead of 1
	rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2, 0)); // 1 at y -- up, 1 at x -- right, 1 at z -- closer to me

	
	// -------------------- SHADER PROGRAM LINKING
	GLuint v_addr = glGetUniformLocation(shaderProgram, "view_matrix");
	GLuint m_addr = glGetUniformLocation(shaderProgram, "m_matrix");
	GLuint p_addr = glGetUniformLocation(shaderProgram, "p_matrix");
	glUniformMatrix4fv(v_addr, 1, false, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(v_addr, 1, false, glm::value_ptr(grid_matrix));
	glUniformMatrix4fv(v_addr, 1, false, glm::value_ptr(coord_matrix));
	glUniformMatrix4fv(p_addr, 1, false, glm::value_ptr(perspective));


	// ----------------- RESET VIEW
	update_view();

	glm::mat4 temp_model_matrix = glm::mat4(1.0f);

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		
		glUniformMatrix4fv(
			pers_addr, 1, GL_FALSE, glm::value_ptr(perspective));

		// ------------------------- X Y ZPRINT COORDINATES
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindVertexArray(coord_VAO);
		glLineWidth(3.f);

		/*glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));*/
		glUniformMatrix4fv(
			coord_addr, 1, GL_FALSE, glm::value_ptr(coord_matrix));
		glDrawArrays(GL_LINES, 0, 6);// v.size()

		// PRINT GRID
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindVertexArray(grid_VAO);
		glLineWidth(1.f);

		// ////////////////////// RECORD MODEL  
		temp_model_matrix = grid_matrix;
		//center grid

		_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, 0));
		_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(-1, 0, 0));

		// transform matrix -- // Grid on X and Z plane
		grid_matrix *= _rotat;
		grid_matrix *= _trans;
		

		// draw
		//glUniformMatrix4fv(
		//	model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(
			grid_addr, 1, GL_FALSE, glm::value_ptr(grid_matrix));
		glDrawArrays(GL_TRIANGLES, 0, v.size());// v.size()

		////////////////////////// RESET
		grid_matrix = temp_model_matrix;

		// ---------------------------------- TORSO (Base)--------------------------
		// ----------------- TORSO TRANSFORM MATRIX

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(square_VAO);
		glLineWidth(1.f);

		// record model 
		temp_model_matrix = model_matrix;

		setTorso();

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;
		temp_model_matrix = model_matrix;
		// ------------------ HEAD --------------------------------

		/*_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(-35.f), glm::vec3(0, 0, -1));
		_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-1, 16, 0));
		_scale = glm::scale(glm::mat4(1.0f), glm::vec3(3, 1, 1));
		model_matrix = glm::mat4(1.0f);
		model_matrix *= _rotat;
		model_matrix *= _trans;
		model_matrix *= _scale;*/
		setHeadMatrix();
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;
		temp_model_matrix = model_matrix;

		// ------------------ NECK --------------------------------

		setNeck();
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------ UPPER_LEG 1 --------------------------------
		temp_model_matrix = model_matrix;

		setUpperLeg1();
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------ UPPER_LEG 2 --------------------------------
		temp_model_matrix = model_matrix;

		setUpperLeg2();

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------ LOWER_LEG 1 --------------------------------
		temp_model_matrix = model_matrix;

		setLowerLeg1();

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------ LOWER_LEG 2 --------------------------------
		temp_model_matrix = model_matrix;

		setLowerLeg2();

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------ UPPER_ARM 1 --------------------------------
		temp_model_matrix = model_matrix;

		setUpperArm1();

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;


		//glUniformMatrix4fv(
		//	camera_addr, 1, GL_FALSE, glm::value_ptr(view_matrix));

		// ------------------ UPPER_ARM 2 --------------------------------
		temp_model_matrix = model_matrix;
		setUpperArm2();

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------ LOWER_ARM 1 --------------------------------
		setLowerArm1();
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		glUniformMatrix4fv(
			camera_addr, 1, GL_FALSE, glm::value_ptr(view_matrix));

		// ------------------ LOWER_ARM 2 --------------------------------
		temp_model_matrix = model_matrix;

		setLowerArm2();
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ////////////////////////////////////////////////////////////CAMERA
		glUniformMatrix4fv(
			camera_addr, 1, GL_FALSE, glm::value_ptr(view_matrix));

	}

	glfwTerminate();
	return EXIT_SUCCESS;

}

