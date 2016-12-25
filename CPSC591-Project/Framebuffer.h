#pragma once

#include "Libraries\glew\glew.h"

/*
	Represents an OpenGL framebuffer.
	Contains the API for setting a framebuffer up,
	as well as activating and deactivating it
*/
class Framebuffer
{
public:
	Framebuffer();
	~Framebuffer();

	/*
		Creates a framebuffer.
		This create an ID for the buffer,
		as well as all the textures and other stuff (should be defined by the subclass)
	*/
	virtual void create();
	
	/*
		Binds the framebuffer
	*/
	void bind();

	/*
		Unbinds the framebuffer
	*/
	void unbind();

private:
	GLuint fbo;				//framebuffer's ID
};

