#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, /* (x, y, z) */
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};

	/* Create Vertex Buffer Object (VBO) */
	unsigned int VBO;
	/* Generate buffer object with a buffer ID */
	glGenBuffers(1, &VBO);

	/* Bind the newly created buffer object to GL_ARRAY_BUFFER target */
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Copy the vertex data into the currently bound buffer's memory */
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW /* How we want graphics card to manage the data */
	);

	/*********************/
	/**** RENDER LOOP ****/
	/*********************/
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