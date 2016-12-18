#include "SSAOFirstPassFramebuffer.h"
#include "SceneParameters.h"



SSAOFirstPassFramebuffer::SSAOFirstPassFramebuffer()
{
	normalTexture = NULL;
	colorTexture = NULL;
	specularTexture = NULL;
	depthTexture = NULL;
}


SSAOFirstPassFramebuffer::~SSAOFirstPassFramebuffer()
{
}

void SSAOFirstPassFramebuffer::create() {
	Framebuffer::create();
	bind();


	GLuint depthTex, normalTex, colorTex, specularTex;

	//Depth buffer
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex); 
	glTexImage2D(GL_TEXTURE_2D,	0, GL_DEPTH_COMPONENT24, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	//Normal buffer
	glGenTextures(1, &normalTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, normalTex, 0);

	//Color buffer
	glGenTextures(1, &colorTex);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, colorTex, 0);

	//Specular buffer
	glGenTextures(1, &specularTex);
	glBindTexture(GL_TEXTURE_2D, specularTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, specularTex, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Redirect output to correct textures 
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, attachments);

	//Check for errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Could not create SSAO First Pass FB" << std::endl;

	unbind();

	//store textures
	depthTexture = new Texture(GL_TEXTURE_2D, depthTex);
	normalTexture = new Texture(GL_TEXTURE_2D, normalTex);
	colorTexture = new Texture(GL_TEXTURE_2D, colorTex);
	specularTexture = new Texture(GL_TEXTURE_2D, specularTex);
}