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
	// the program ID
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



	}

	// use/activate the Shader
	void use();

	// utility uniform functions
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif
