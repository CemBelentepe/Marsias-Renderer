#pragma once
#include <glm/glm.hpp>

class Shader
{
public:
	unsigned int id;
	
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void use();

	void setFloat(const char* name, float value);
	void setInt(const char* name, int value);
	void setVec3f(const char* name, float v0, float v1, float v2);
	void setMat4f(const char* name, glm::mat4 matrix);
};

