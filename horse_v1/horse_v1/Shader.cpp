#include "stdafx.h"
#include <vector>
//#include <stdio.h>
//#include <cstring>
#include <iostream>
#include <glm.hpp>
#include "Shader.h"


GLuint Shader(std::string vertex_shader_path, std::string fragment_shader_path) {

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