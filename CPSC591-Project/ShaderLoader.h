#pragma once

#include "Libraries\glew\glew.h"
#include <string>

class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();

	GLuint loadShader(std::string vertexShaderPath, std::string fragmentShaderPath);

private:
	std::string readFile(const char * filename);
};

