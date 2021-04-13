#version 330 core

out vec4 FragColor;

in vec3 ourColor; 
in vec2 TexCoord;

//uniform vec4 ourColor;
uniform sampler2D texture1; // To pass the texture image to Fragment shader. We will do it in application.
uniform sampler2D texture2; // To pass the texture image to Fragment shader. We will do it in application.

void main()
{
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//FragColor = vertexColor;
	//FragColor = vec4(ourColor, 1.0f);
	//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);
	FragColor = mix(texture(texture1, TexCoord),
	                texture(texture2, TexCoord), 
					0.2 // 0.0 returns 1st input, 1.0 returns 2nd input, 0.2 returns 80% of 1st and 20% of 2nd
					);
}