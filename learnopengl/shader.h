#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get the required OpenGL headers

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	// the shader program ID
	unsigned int ID;

	// constructor reads and builds the shader
	Shader(const char* vertexPath, const char* fragmentpath) 
	{
		/*************************************************************/
		/* 1. Retrieve the vertex/fragment source code from filepath */
		/*************************************************************/
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::string vertexCode;
		std::string fragmentCode;

		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentpath);

			// read file's buffer contents into stream
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// close file handlers
			vShaderFile.close();
			fShaderFile.close();

			// convert stream to string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch(std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}

		// convert string to char buffer
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		/*************************************************************/
		/* 2. Compile and link shaders                               */
		/*************************************************************/
		int success;
		char infoLog[512];

	    /** VERTEX SHADER **/
		unsigned int vertexShader;							// Create a variable to store the vertexShader object
		vertexShader = glCreateShader(GL_VERTEX_SHADER);	// Generate/Create vertexShader object
		/* Attach the source code to shader object and compile (run-time) the shader */
		glShaderSource(vertexShader,
			1, /* Number of strings to pass*/
			&vShaderCode,
			NULL
		);
		glCompileShader(vertexShader);
		/* Check compilation status */
		
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
			&fShaderCode,
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
		ID = glCreateProgram();	// Generate/Create shaderProgram object
		/* Attach the shaders to the program and link it */
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		/* Check linking status of the shader program */
		/* This function returns a parameter from a shader object */
		glGetProgramiv(ID,
			GL_LINK_STATUS,
			&success
		);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		/* Delete the shader objects after linking, as we do not need this anymore */
		glDeleteShader(ID);
		glDeleteShader(ID);
	}

	// use/activate the Shader
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
