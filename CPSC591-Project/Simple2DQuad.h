#pragma once

#include "Libraries\glew\glew.h"

class Simple2DQuad
{
public:
	Simple2DQuad();
	~Simple2DQuad();

	void draw();
private:
	void create();

	GLuint vao;
};

