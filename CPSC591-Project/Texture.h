#pragma once

#include <string>
#include <iostream>
#include "Libraries\glew\glew.h"
#include "Libraries\stb_image.h"

class Texture
{
public:
	Texture(GLenum TextureTarget, const std::string& FileName);
	Texture(GLenum TextureTarget, GLuint TextureObject);

	bool Load();

	void Bind(GLenum TextureUnit);
	void unBind(GLenum TextureUnit);

//private:
	std::string fileName;
	GLenum textureTarget;
	GLuint textureObj;
};

