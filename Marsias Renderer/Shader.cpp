#include "Shader.h"
#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

#include "Log.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	this->id = glCreateProgram();
	
	std::ifstream vertexFile, fragFile;
	vertexFile.open(vertexShaderPath);
	fragFile.open(fragmentShaderPath);
	std::stringstream vertexStream, fragStream;
	vertexStream << vertexFile.rdbuf();
	fragStream << fragFile.rdbuf();
	
	std::string vertexCode = vertexStream.str();
	std::string fragCode = fragStream.str();
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragShaderSource = fragCode.c_str();

	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		LOG("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog);
	}

	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
		LOG("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog);
	}

	glAttachShader(this->id, vertexShader);
	glAttachShader(this->id, fragShader);
	glLinkProgram(this->id);
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		LOG("ERROR::SHADER::PROGRAM::LINKING_FAILED");
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}

void Shader::use()
{
	glUseProgram(this->id);
}

void Shader::setFloat(const char* name, float value)
{
	glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::setInt(const char* name, int value)
{
	glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setVec3f(const char* name, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(this->id, name), v0, v1, v2);
}

void Shader::setMat4f(const char* name, glm::mat4 matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, GL_FALSE, glm::value_ptr(matrix));
}
