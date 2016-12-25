#include "Framebuffer.h"



Framebuffer::Framebuffer()
{
}


Framebuffer::~Framebuffer()
{
}

void Framebuffer::create() {
	//in here we only create the VBO
	glGenFramebuffers(1, &fbo);
}

void Framebuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void Framebuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}