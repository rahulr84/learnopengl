#version 330 core

layout(location = 0) in vec3 aPos; // position has attribute location 0
layout(location = 1) in vec3 aColor; // color has attribute location 1
layout(location = 2) in vec2 aTexCoord; // texture has attribute location 2

out vec3 ourColor; // specify a color output to the Fragment shader
out vec2 TexCoord; // To pass the texture to Fragment Shader

//uniform mat4 transform; // Transformation matrix to be set in the application
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	//gl_Position = vec4(aPos, 1.0f);
	ourColor = aColor; //set ourColor to the input color from the vertex data
	TexCoord = aTexCoord;
}