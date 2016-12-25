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
	//create and bind the framebuffer
	Framebuffer::create();
	bind();


	GLuint depthTex, normalTex, colorTex, specularTex;

	//Create the depth buffer
	//This step is important, otherwise
	//there will be no depth test performed
	glGenTextures(1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex); 
	//24 bits is enough to store depth for our case
	glTexImage2D(GL_TEXTURE_2D,	0, GL_DEPTH_COMPONENT24, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
	//attach the texture as a depth attachement
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);

	//Create the normal buffer
	glGenTextures(1, &normalTex);
	glBindTexture(GL_TEXTURE_2D, normalTex);
	//normal is stored as a simple RGB thingy (values are from 0 to 1 in R^3)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//attach the texture as the 0'th attachement
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, normalTex, 0);

	//Create the color buffer
	glGenTextures(1, &colorTex);
	glBindTexture(GL_TEXTURE_2D, colorTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, colorTex, 0);

	//Create the specular buffer
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