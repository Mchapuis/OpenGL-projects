#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

uniform mat4 view_matrix; // used for camera
uniform mat4 p_matrix; // used for camera
uniform mat4 m_matrix; // name referenced with a string in glGetUniformLocation

out vec3 triangleColor;

void main()
{
	gl_Position = p_matrix * view_matrix * m_matrix * vec4(pos, 1);
	triangleColor = color;

}