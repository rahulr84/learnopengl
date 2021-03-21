#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

	/*********************/
	/**** RENDER LOOP ****/
	/*********************/
	while (!glfwWindowShouldClose(window))
	{
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