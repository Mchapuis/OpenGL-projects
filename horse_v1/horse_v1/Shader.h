#ifndef SHADER_H
#define SHADER_H

#include "stdafx.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
class Shader
{
public:
	GLuint ProgramID;

	// Constructor
	Shader(std::string, std::string){
		GLuint VertexShaderID;
		GLuint FragmentShaderID;
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream;
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream;
		GLint Result;

		char const * VertexSourcePointer = VertexShaderCode.c_str();
		char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	};
};

#endif
