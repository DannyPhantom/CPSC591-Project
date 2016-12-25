#pragma once

#include "Framebuffer.h"
#include "Texture.h"

/*
	Framebuffer for the second SSAO pass,
	i.e. the actual AO calculations
*/
class SSAOSecondPassFramebuffer : public Framebuffer
{
public:
	SSAOSecondPassFramebuffer();
	~SSAOSecondPassFramebuffer();

	/*
		@see Framebuffer::create()
	*/
	void create();

public:
	Texture *ssaoTexture;
};

