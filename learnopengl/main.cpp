#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define LEARN_GLM

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

#ifdef LEARN_GLM
/* Main function for GLM operations */
int main()
{
	/* Translate a vector (1, 0, 0) by (1, 1, 0) */
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f); // Input vector
	glm::mat4 trans = glm::mat4(1.0f); // Initialize 4x4 matrix as Identity matrix
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f)); // Create transformation matrix using translation vector (1, 1, 0)
	vec = trans * vec; // Output the transformed vector
	std::cout << vec.x << vec.y << vec.z << std::endl;

	return 0;
}
#else
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
#if 0
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
#else /* Cube */
	float vertices[] = {
		//positions           // colors          // tex coords
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f ),
		glm::vec3( 2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f ),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f ),
		glm::vec3(-1.7f,  3.0f, -7.5f ),
		glm::vec3( 1.3f, -2.0f, -2.5f ),
		glm::vec3( 1.5f,  2.0f, -2.5f ),
		glm::vec3( 1.5f,  0.2f, -1.5f ),
		glm::vec3(-1.3f,  1.0f, -1.5f )
	};
#endif
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
#if 0 /* undefine this for Cube program */
	unsigned int EBO;					// Create a variable to store the EBO object
	glGenBuffers(1, &EBO);				// Generate buffer object with a buffer ID 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Bind the newly created buffer object to GL_ELEMENT_ARRAY_BUFFER target 
	/* Copy the vertex data into the currently bound buffer's memory */
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices),
		indices,
		GL_STATIC_DRAW /* How we want graphics card to manage the data */
	);
#endif
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

	/* Tell OpenGL to which texture each shader sampler belongs to */
	ourShader.use();
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);

	/*********************************************************************/
	/* 7. Transformations                                                */
	/*********************************************************************/
#if 0 //  Keep the transformation inside the render loop to change every frame 
	glm::mat4 trans = glm::mat4(1.0f); // Initialize 4x4 matrix as Identity matrix
	// Rotate 90 deg around the Z axis
	trans = glm::rotate(trans,		// Transformation matrix
		glm::radians(90.0f),		// Degree in radians
		glm::vec3(0.0, 0.0, 1.0) // Axis of rotation (Z axis)
	); 
	// Scale by 0.5 on each axis
	trans = glm::scale(trans,		// Transformation matrix
		glm::vec3(0.5, 0.5, 0.5) // scale factor for each axis
	);
	// Pass the transformation matrix to the vertex shader
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
#endif

	// Enable Depth test using Z buffer or Depth buffer
	glEnable(GL_DEPTH_TEST);

	/*********************************************************************/
	/* 8. RENDER LOOP                                                    */
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
			GL_COLOR_BUFFER_BIT |/* the Buffer you want to fill (we chose color buffer) */ \
			GL_DEPTH_BUFFER_BIT /* For Depth testing */
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

		/* Transformation */
#if 0
		glm::mat4 trans = glm::mat4(1.0f); // Initialize 4x4 matrix as Identity matrix
		// Translation on each axis
		trans = glm::translate(trans,		// Transformation matrix
			glm::vec3(0.5f, -0.5f, 0.0f) // translate  factor for each axis
		);
		// Rotate 90 deg around the Z axis
		trans = glm::rotate(trans,		// Transformation matrix
			(float)glfwGetTime(),		// Degree in radians (pass the time)
			glm::vec3(0.0f, 0.0f, 1.0f) // Axis of rotation (Z axis)
		);

		// Pass the transformation matrix to the vertex shader
		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
#else 
		/* Transformation which looks like the object is laying on the floor */
		// View Matrix
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Move the scene on Z axis in reverse direction
		unsigned int transformLocView = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(transformLocView, 1, GL_FALSE, glm::value_ptr(view));

		// Projection Matrix
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		unsigned int transformLocProj = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(transformLocProj, 1, GL_FALSE, glm::value_ptr(projection));

		// Model Matrix
		// For loop to access each cube according to its position
		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 1.0f, 1.0f)); // Rotate on multiple axis time*-55 degrees for Cube
			unsigned int transformLocModel = glGetUniformLocation(ourShader.ID, "model");
			glUniformMatrix4fv(transformLocModel, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(GL_TRIANGLES, /* Primitive */
				0, /* starting index of vertex array*/
				36 /* num vertices for Cube */
			);
		}
#endif

#if 1
		/* Start drawing using the currently active shader,
		   the previously defined vertex attribute configuration and 
		   with the VBO's vector data (indirectly bound via the VBO) */
		//glDrawArrays(GL_TRIANGLES, /* Primitive */
		//	0, /* starting index of vertex array*/
		//	36 /* num vertices for Cube */
		//);
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
#endif