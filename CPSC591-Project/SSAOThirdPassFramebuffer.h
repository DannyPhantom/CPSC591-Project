#pragma once

#include "Framebuffer.h"
#include "Texture.h"

/*
	Framebuffer for the third SSAO pass,
	i.e. the blur stage
*/
class SSAOThirdPassFramebuffer : public Framebuffer
{
public:
	SSAOThirdPassFramebuffer();
	~SSAOThirdPassFramebuffer();

	/*
		@see Framebuffer::create()
	*/
	void create();

public:
	Texture *blurredSSAOTexture;
};

