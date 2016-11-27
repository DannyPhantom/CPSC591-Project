#include "SSAOSecondPassFramebuffer.h"
#include "SceneParameters.h"


SSAOSecondPassFramebuffer::SSAOSecondPassFramebuffer()
{
}


SSAOSecondPassFramebuffer::~SSAOSecondPassFramebuffer()
{
}

void SSAOSecondPassFramebuffer::create() {
	Framebuffer::create();
	bind();

	//SSAO texture
	GLuint ssaoTex;
	glGenTextures(1, &ssaoTex);
	glBindTexture(GL_TEXTURE_2D, ssaoTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoTex, 0); 
	
	GLuint attachments[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, attachments);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Could not create SSAO FB" << std::endl;

	unbind();

	//store the texture
	ssaoTexture = new Texture(GL_TEXTURE_2D, ssaoTex);
}
