#version 330 core

out vec4 FragColor;

in vec3 ourColor; 
in vec2 TexCoord;

//uniform vec4 ourColor;
uniform sampler2D ourTexture; // To pass the texture image to Fragment shader. We will do it in application.

void main()
{
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = vertexColor;
	//FragColor = vec4(ourColor, 1.0f);
	FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
}