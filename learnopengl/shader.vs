#version 330 core

layout(location = 0) in vec3 aPos; // position has attribute location 0
layout(location = 1) in vec3 aColor; // color has attribute location 1
out vec3 ourColor; // specify a color output to the Fragment shader

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	ourColor = aColor; //set ourColor to the input color from the vertex data
}