#include "SSAOFirstPassFramebuffer.h"
#include "SceneParameters.h"



SSAOFirstPassFramebuffer::SSAOFirstPassFramebuffer()
{
	positionTexture = NULL;
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


	GLuint positionTex, normalTex, colorTex, specularTex;

	//Position buffer
	glGenTextures(1, &positionTex);
	glBindTexture(GL_TEXTURE_2D, positionTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, positionTex, 0);

	//Normal buffer
	glGenTextures(1, &normalTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normalTex, 0);

	//Color buffer
	glGenTextures(1, &colorTex);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, colorTex, 0);

	//Specular buffer
	glGenTextures(1, &specularTex);
	glBindTexture(GL_TEXTURE_2D, specularTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, specularTex, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Redirect output to correct textures 
	GLuint attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);

	//Create depth buffer
	GLuint depthTex;
	glGenRenderbuffers(1, &depthTex);
	glBindRenderbuffer(GL_RENDERBUFFER, depthTex);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthTex);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//Check for errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Could not create SSAO First Pass FB" << std::endl;

	unbind();

	//store textures
	positionTexture = new Texture(GL_TEXTURE_2D, positionTex);
	normalTexture = new Texture(GL_TEXTURE_2D, normalTex);
	colorTexture = new Texture(GL_TEXTURE_2D, colorTex);
	specularTexture = new Texture(GL_TEXTURE_2D, specularTex);
	depthTexture = new Texture(GL_TEXTURE_2D, depthTex);
}