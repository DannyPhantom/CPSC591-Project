#pragma once

#include "Libraries\glew\glew.h"

class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();

	virtual void create();
	
	void bind();
	void unbind();

private:
	GLuint fbo;
};

