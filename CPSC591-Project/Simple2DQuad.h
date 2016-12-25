#pragma once

#include "Libraries\glew\glew.h"

/*
	Represents a simple 2D Quad 
	that is drawn to the screen 
	(this is done fullscreen).
	Here's the difference between this class and TexturedObject2D:
		TexturedObject2D takes a texture as a parameter, this one doesn't
		TexturedObject2D takes a program as a parameter, this one doesn't
	Therefore, this class has to be surrounded with the glUseProgram call, 
	as well as any other calls as desired (i.e. texture attachements, etc.)
	The only requirement is that the shader has to use vertices as in location=0,
	and uv's have to be in location=1
*/
class Simple2DQuad
{
public:
	Simple2DQuad();
	~Simple2DQuad();

	/*
		Issues a draw call
	*/
	void draw();
private:

	/*
		Generates VBO's and VAO
	*/
	void create();

	GLuint vao;
};

