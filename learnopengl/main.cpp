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

/* Vertex Shader Code Source */
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos; \n"
"out vec4 vertexColor; // specify a color output to the Fragment shader \n"
"void main()\n"
"{ \n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f); \n"
"   vertexColor = vec4(0.5f, 0.0f, 0.0f, 0.0f); // output variable to dark red \n"
"}\0";

/* Fragement Shader Code Source */
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"in vec4 vertexColor; \n "
"uniform vec4 ourColor; \n"
"void main()\n"
"{ \n"
"	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
"	//FragColor = vertexColor; \n"
"	FragColor = ourColor; \n"
"}\0";

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
#if 1 /* Triangle Vertices */
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, /* (x, y, z) */
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
#else /* Rectangle vertices and indices */
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, // top right (index 0)
		 0.5f, -0.5f, 0.0f, // bottom right (index 1)
		-0.5f, -0.5f, 0.0f, // bottom left (index 2)
		-0.5f,  0.5f, 0.0f, // top left (index 3)
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
#endif

	/* Use Vertex Array Object (VAOs) to store the Vertex configurations */
	unsigned int VAO;			// Create a variable to store the VAO object
	glGenVertexArrays(1, &VAO); // Generate array object
	glBindVertexArray(VAO);		// Bind the VAO to use it 

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

	/* Linking Vertex Attributes */
	glVertexAttribPointer(0, /* layout (location=0) in Vertex shader */
		3,			/* vec3 in vertex shader */
		GL_FLOAT,	/* vec* in GLSL is a float */
		GL_FALSE,	/* Normalize? not required for float, only for int*/
		3 * sizeof(float), /* stride (space between consecutive vertex attributes) */
		(void*) 0 /* offset of where the position data begins in buffer */
	);
	glEnableVertexAttribArray(0 /* vertex attribute location (layout (location=0) in Vertex shader) */
	);

	/** VERTEX SHADER **/
	unsigned int vertexShader;							// Create a variable to store the vertexShader object
	vertexShader = glCreateShader(GL_VERTEX_SHADER);	// Generate/Create vertexShader object
	/* Attach the source code to shader object and compile (run-time) the shader */
	glShaderSource(vertexShader,
		1, /* Number of strings to pass*/
		&vertexShaderSource,
		NULL
	);
	glCompileShader(vertexShader);
	/* Check compilation status */
	int success;
	char infoLog[512];
	/* This function returns a parameter from a shader object */
	glGetShaderiv(vertexShader,
		GL_COMPILE_STATUS,
		&success
	);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/** FRAGMENT SHADER **/
	unsigned int fragmentShader;						// Create a variable to store the fragmentShader object
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);// Generate/Create fragmentShader object
	/* Attach the source code to shader object and compile (run-time) the shader */
	glShaderSource(fragmentShader,
		1, /* Number of strings to pass*/
		&fragmentShaderSource,
		NULL
	);
	glCompileShader(fragmentShader);
	/* Check compilation status */
	/* This function returns a parameter from a shader object */
	glGetShaderiv(fragmentShader,
		GL_COMPILE_STATUS,
		&success
	);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	/** SHADER PROGRAM **/
	unsigned int shaderProgram;			// Create a variable to store the shaderProgram object
	shaderProgram = glCreateProgram();	// Generate/Create shaderProgram object
	/* Attach the shaders to the program and link it */
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	/* Check linking status of the shader program */
	/* This function returns a parameter from a shader object */
	glGetProgramiv(shaderProgram,
		GL_LINK_STATUS,
		&success
	);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	/* Delete the shader objects after linking, as we do not need this anymore */
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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

		/* Use/Activate the shader program */
		glUseProgram(shaderProgram);

		/* Bind the VAO to use it */
		glBindVertexArray(VAO);

		/* Access and set the color in fragment shader */
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		/* set the color changing over time */
		float timeValue = glfwGetTime();
		//std::cout << "TimeValue : "<< timeValue << std::endl;
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//std::cout << "greenValue : "<< greenValue << std::endl;
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		/* Start drawing using the currently active shader,
		   the previously defined vertex attribute configuration and 
		   with the VBO's vector data (indirectly bound via the VBO) */
		glDrawArrays(GL_TRIANGLES, /* Primitive */
			0, /* starting index of vertex array*/
			3 /* num vertices */
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