// template.cpp : Defines the entry point for the console application.
//

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
#include "Grid.h"
#include "Shader.h"



///#endif STDAFX_H
//----------------- VIEW MATRIX
glm::vec3 camera_pos = glm::vec3(0.0, 30.0, 40.5); // -10 at z(2.2, 60.0, 50.5)
glm::vec3 camera_tar = glm::normalize(glm::vec3(0, 0, 1)); // or direction...need to be normalized!
glm::vec3 camera_up = glm::vec3(0, 2, 0);// up in the y position
glm::mat4 view_matrix;

const GLuint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
GLFWwindow* window;


// when right arrow is pressed, teddy is rotating
// when right arrow is release, teddy stops
bool b_rotateTeddy = false;

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
	
	if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
		b_rotateTeddy = false;
	}

	if (key == GLFW_KEY_RIGHT){
		b_rotateTeddy = true;
	}
	
}

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

	// Link the program
	//----------------------------------- recap of the steps:
	// 1- glCreateShader (for vs and ps)
	// 2- glShaderSource (for vs and ps)
	// 3- glCompileShader (for vs and ps)
	// 4- glCreateProgram 
	// 5- attach vs and ps to the program
	// 6- Construction
	// 7- utilisation
	// 8- glDeleteProgram, glDeleteShader (for vs and ps)
	//-------------------------------------------------------
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

// if window is nullptr or glewInit is not equal to GLEW_OK, return -1
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

	//---------------- MODEL MATRIX
	
	glm::mat4 model_matrix = glm::mat4(1.0f); // identity  --- this will be used for scale, transform and rotation
	glm::mat4 scale = glm::mat4(1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	glm::mat4 rotat = glm::mat4(1.0f);

	//----------------- GRID
	glm::mat4 grid = glm::mat4(1.0f);
	

	//----------------- PROJECTION MATRIX
	//45 is the FOV, fraction is the aspect ratio, never put zero, calculate only after/before in z
	glm::mat4 perspective = glm::perspective(glm::radians(90.0f), 8.0f / 6.0f, 0.1f, 150.0f);

	// model addresse referenced in vertex shader... we know where to send information
	//-------------------FOR THE SHADER PROGRAM
	GLuint model_addr = glGetUniformLocation( // returns an integer that represents the location of a specific uniform variable within a program object
		shaderProgram, "m_matrix");
	GLuint camera_addr = glGetUniformLocation(
		shaderProgram, "view_matrix");
	GLuint pers_addr = glGetUniformLocation(
		shaderProgram, "p_matrix");

	//GLuint model_temp_addr = glGetUniformLocation(
		//shaderProgram, "m_matrix");

	
	// --------------------BACKGROUND COLOR
	// red, green, blue, alpha
	glClearColor(0.7f, 0.7f, 0.7f, 1);

	// -----------------MODEL MATRIX ------------------------
	
	scale = glm::scale(glm::mat4(1.0f), glm::vec3(40, 40, 40)); // so now the identity matrix is .5 instead of 1
	rotat = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 0, -1));
	trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2, 0)); // 1 at y -- up, 1 at x -- right, 1 at z -- closer to me

	
	//model_matrix ;//rotat
	
	// -------------------- SHADER PROGRAM LINKING
	GLuint v_addr = glGetUniformLocation(shaderProgram, "view_matrix");
	GLuint m_addr = glGetUniformLocation(shaderProgram, "m_matrix");
	GLuint p_addr = glGetUniformLocation(shaderProgram, "p_matrix");
	glUniformMatrix4fv(v_addr, 1, false, glm::value_ptr(model_matrix));
	glUniformMatrix4fv(p_addr, 1, false, glm::value_ptr(perspective));
	/*
	GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");
	glUniform3f(uniColor, 0.5f, 0.5f, 0.0f);
	*/

	// ---------------- AUTOMATIC ANIMATION
	//auto t_start = std::chrono::high_resolution_clock::now();

	// ----------------- RESET VIEW
	update_view();

	// old lookat function
	//glm::mat4 view_matrix = glm::lookAt(
	//	glm::vec3(2.2f, 60.0f, 50.5f),
	//	glm::normalize(glm::vec3(0, 0, -10)),//glm::vec3(0.0f, 0.0f, 0.0f),
	//	glm::vec3(0.0f, 0.0f, 2.0f)
	//	);

	// to record matrix and reseting it in the loop
	glm::mat4 temp_model_matrix = glm::mat4(1.0f);

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUniformMatrix4fv(
			pers_addr, 1, GL_FALSE, glm::value_ptr(perspective));

		// PRINT COORDINATES
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindVertexArray(coord_VAO);
		glLineWidth(3.f);

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_LINES, 0, 6);// v.size()

		// PRINT GRID
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindVertexArray(grid_VAO);
		glLineWidth(1.f);

		// record model 
		temp_model_matrix = model_matrix;
		//center grid
		glm::mat4 grid_rotate = glm::mat4(1.0f);
		glm::mat4 grid_translate = glm::mat4(1.0f);
		grid_translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, -1, 0));
		grid_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(-1, 0, 0));

		// transform matrix -- // Grid on X and Z plane
		model_matrix = grid_translate;
		model_matrix *= grid_rotate;

		// draw
		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, v.size());// v.size()

		//reset model
		model_matrix = temp_model_matrix;

		// ---------------------------------- BODY (Base)--------------------------
		// ----------------- BODY TRANSFORM MATRIX

		glm::mat4 _trans = glm::mat4(1.0f);
		glm::mat4 _rotat = glm::mat4(1.0f);
		glm::mat4 _scale = glm::mat4(1.0f);
		_trans = glm::translate(glm::mat4(1.0f), glm::vec3(0, 10, 0));
		_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(90.f), glm::vec3(-1, 0, 0));
		_scale = glm::scale(glm::mat4(1.0f), glm::vec3(5, 2, 1));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glBindVertexArray(square_VAO);
		glLineWidth(1.f);

		// record model 
		temp_model_matrix = model_matrix;

		model_matrix = _trans;
		model_matrix *= _scale;

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()

		// reset model
		model_matrix = temp_model_matrix;

		// ------------------HEAD--------------------------------
		temp_model_matrix = model_matrix;

		glm::mat4 test_trans = glm::mat4(1.0f);
		_rotat = glm::rotate(glm::mat4(1.0f), glm::radians(-25.f), glm::vec3(0, 0, -1));
		_trans = glm::translate(glm::mat4(1.0f), glm::vec3(-3, 14, 0));
		_scale = glm::scale(glm::mat4(1.0f), glm::vec3(3, 1, 1));
		model_matrix *= _rotat;
		model_matrix *= _trans;
		model_matrix *= _scale;
		
		
		

		glUniformMatrix4fv(
			model_addr, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glDrawArrays(GL_TRIANGLES, 0, s.size());// v.size()


		glUniformMatrix4fv(
			camera_addr, 1, GL_FALSE, glm::value_ptr(view_matrix));
		// reset model
		model_matrix = temp_model_matrix;
		
		//glBindVertexArray(coord_VAO);
		//glLineWidth(3.f);
		//glDrawArrays(GL_LINES, 0, 6);// v.size()
		//glBindVertexArray(0);

		//glBindVertexArray(grid_VAO);
		//glLineWidth(3.f);
		//glDrawArrays(GL_TRIANGLES, 0, v.size());// v.size()
		//glBindVertexArray(0);
		//glBindVertexArray(0);
	}

	glfwTerminate();
	return EXIT_SUCCESS;

}

