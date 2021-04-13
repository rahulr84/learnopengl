#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* Function to process the user input using keys to the window */
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

/* Callback function to be used when a user resizes the window */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	/* Tell OpenGL the size of the rendering window, so that OpenGL knows how
	   we want to display the data and coordinates w.r.t the window*/
	glViewport(0, 0,    /* lower left corner of the rendering window */
		800, 600 /* Width and Height of the rendering window*/
	);
}

/* Main function */
int main()
{
	/*****************************/
	/**** SETUP GLFW AND GLAD ****/
	/*****************************/

	glfwInit(); // Initialize GLFW

	/* Configure GLFW using glfwWindowHint functions */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a Window object */
	GLFWwindow* window = glfwCreateWindow(800, /* Width */
		600, /* Height */
		"LearnOpenGL", /* Name of the window */
		NULL, NULL /* Ignore these arguments */
	);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	/* Make the context of our window the main context on the current thread */
	glfwMakeContextCurrent(window);

	/* Initialize GLAD */
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* Set the callback function to GLFW */
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*********************************/
	/**** SETUP GRAPHICS PIPELINE ****/
	/*********************************/

	/* Vertex Data :
	   Normalized 3D device coordinates in the range between -1.0 and 1.0 */
#if 0 /* Triangle Vertices */
	float vertices[] = {
		//positions         // colors
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top
	};
#else /* Rectangle vertices and indices */
	float vertices[] = {
		//positions           // colors           // tex coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right (index 0)
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right (index 1)
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left (index 2)
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // top left (index 3)
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
#endif

	/*********************************************************************/
	/* 1. Create and bind Vertex Array Object (VAO)                      */
	/*********************************************************************/
	/* Use Vertex Array Object (VAOs) to store the Vertex configurations */
	unsigned int VAO;			// Create a variable to store the VAO object
	glGenVertexArrays(1, &VAO); // Generate array object
	glBindVertexArray(VAO);		// Bind the VAO to use it 

	/*********************************************************************/
	/* 2. Create Vertex Buffer Object (VBO) and copy our vertices array  */
	/*    to the VBO for OpenGL to use                                   */
	/*********************************************************************/
	/* Create Vertex Buffer Object (VBO) */
	unsigned int VBO;					// Create a variable to store the VBO object
	glGenBuffers(1, &VBO);				// Generate buffer object with a buffer ID 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the newly created buffer object to GL_ARRAY_BUFFER target 
	/* Copy the vertex data into the currently bound buffer's memory */
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW /* How we want graphics card to manage the data */
	);

	/*********************************************************************/
	/* 3. Create Element Buffer Object (EBO) and copy our indices array  */
	/*    to the EBO for OpenGL to use                                   */
	/*********************************************************************/
	/* Create Element Buffer Object (EBO) */
	unsigned int EBO;					// Create a variable to store the EBO object
	glGenBuffers(1, &EBO);				// Generate buffer object with a buffer ID 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the newly created buffer object to GL_ELEMENT_ARRAY_BUFFER target 
	/* Copy the vertex data into the currently bound buffer's memory */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW /* How we want graphics card to manage the data */
	);

	/*********************************************************************/
	/* 4. Set and link Vertex Attribute pointers                         */
	/*********************************************************************/
	/* Position Attribute */
	glVertexAttribPointer(0, /* layout (location=0) in Vertex shader */
		3,			/* vec3 in vertex shader */
		GL_FLOAT,	/* vec* in GLSL is a float */
		GL_FALSE,	/* Normalize? not required for float, only for int*/
		8 * sizeof(float), /* STRIDE (space between consecutive vertex attributes) */
		(void*)0 /* OFFSET of where the position data begins in buffer */
	);
	glEnableVertexAttribArray(0 /* vertex attribute location (layout (location=0) in Vertex shader) */
	);
	/* Color Attribute */
	glVertexAttribPointer(1, /* layout (location=1) in Vertex shader */
		3,			/* vec3 in vertex shader */
		GL_FLOAT,	/* vec* in GLSL is a float */
		GL_FALSE,	/* Normalize? not required for float, only for int*/
		8 * sizeof(float), /* STRIDE (space between consecutive vertex attributes) */
		(void*)(3 * sizeof(float)) /* OFFSET of where the position data begins in buffer */
	);
	glEnableVertexAttribArray(1 /* vertex attribute location (layout (location=1) in Vertex shader) */
	);
	/* Texture coordinate Attribute */
	glVertexAttribPointer(2, /* layout (location=2) in Vertex shader */
		3,			/* vec3 in vertex shader */
		GL_FLOAT,	/* vec* in GLSL is a float */
		GL_FALSE,	/* Normalize? not required for float, only for int*/
		8 * sizeof(float), /* STRIDE (space between consecutive vertex attributes) */
		(void*)(6 * sizeof(float)) /* OFFSET of where the position data begins in buffer */
	);
	glEnableVertexAttribArray(2 /* vertex attribute location (layout (location=2) in Vertex shader) */
	);

	/*********************************************************************/
	/* 5. Create shaders and use this in Render loop below               */
	/*********************************************************************/
	Shader ourShader("shader.vs", "shader.fs");

	/*********************************************************************/
	/* 6. Load and create a texture                                      */
	/*********************************************************************/
	/* TEXTURE 1 */
	unsigned int texture1;					// Create a variable to store the texture object
	glGenTextures(1, &texture1);			// Create texture object
	glBindTexture(GL_TEXTURE_2D, texture1);	// Bind the texture to use it 

	/* Set the texture wrapping and filtering options on the currently bound texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Load an image and generate the texture */
	int width1, height1, numChannels1;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* texImage1 = stbi_load("..\\resources\\textures\\container.jpg", &width1, &height1, &numChannels1, 0);

	if (texImage1)
	{
		glTexImage2D(GL_TEXTURE_2D, // texture target
			0, // mipmap level
			GL_RGB, // texture storage format
			width1,
			height1,
			0, // some legacy stuff
			GL_RGB, // format of source image
			GL_UNSIGNED_BYTE, // datatype of source image
			texImage1
		);
		glGenerateMipmap(GL_TEXTURE_2D); // Generate all the required mipmaps for the currently bound texture
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}

	stbi_image_free(texImage1); // free the image memory, after generating texture is done

	/* TEXTURE 2 */
	unsigned int texture2;					// Create a variable to store the texture object
	glGenTextures(1, &texture2);			// Create texture object
	glBindTexture(GL_TEXTURE_2D, texture2);	// Bind the texture to use it 

	/* Set the texture wrapping and filtering options on the currently bound texture */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Load an image and generate the texture */
	int width2, height2, numChannels2;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* texImage2 = stbi_load("..\\resources\\textures\\awesomeface.png", &width2, &height2, &numChannels2, 0);

	if (texImage2)
	{
		glTexImage2D(GL_TEXTURE_2D, // texture target
			0, // mipmap level
			GL_RGB, // texture storage format
			width2,
			height2,
			0, // some legacy stuff
			GL_RGBA, // format of source image
			GL_UNSIGNED_BYTE, // datatype of source image
			texImage2
		);
		glGenerateMipmap(GL_TEXTURE_2D); // Generate all the required mipmaps for the currently bound texture
	}
	else
	{
		std::cout << "Failed to load texture2" << std::endl;
	}

	stbi_image_free(texImage2); // free the image memory, after generating texture is done

	/*********************************************************************/
	/* 7. RENDER LOOP                                                    */
	/*********************************************************************/
	while (!glfwWindowShouldClose(window))
	{
		/* User input through keys */
		processInput(window);

		/** Rendering commands **/

		/* Specify the color you want to to clear the screen (state-setting function) */
		glClearColor(
			0.2f, /* R */
			0.3f, /* G */
			0.3f, /* B */
			1.0f  /* A */
		);
		/* Clear the screen and fill with color specified before (state-using function)*/
		glClear(
			GL_COLOR_BUFFER_BIT /* the Buffer you want to fill (we chose color buffer) */
		);

		/* Activate and bind first texture */
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		/* Activate and bind second texture */
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		/* Bind the VAO to use it */
		glBindVertexArray(VAO);

		/* Use our shader */
		ourShader.use();
		/* Tell OpenGL to which texture each shader sampler belongs to */
		ourShader.setInt("texture1", 0);
		ourShader.setInt("texture2", 1);

#if 0
		/* Start drawing using the currently active shader,
		   the previously defined vertex attribute configuration and 
		   with the VBO's vector data (indirectly bound via the VBO) */
		glDrawArrays(GL_TRIANGLES, /* Primitive */
			0, /* starting index of vertex array*/
			3 /* num vertices */
		);
#else
		glDrawElements(GL_TRIANGLES, /* Primitive */
			6, /* number of elements we would like to draw (total number of indices) */
			GL_UNSIGNED_INT, // type of indices
			0 /* offset */
		);
#endif

		/* Swaps the double buffers */
		glfwSwapBuffers(window);

		/* checks if any events are triggered (like keyboard or mouse events),
		   updates the window state, and
		   calls the corresponding functions via callback methods, which we can define. */
		glfwPollEvents();
	}

	/* Properly clean/delete all of GLFW's resources that were allocated */
	glfwTerminate();

	return 0;
}