#pragma once

#include "Framebuffer.h"
#include "Texture.h"

/*
	Framebuffer for the first SSAO pass.
	This pass create the depth texture,
	normal texture, color texture and 
	the specular texture
*/
class SSAOFirstPassFramebuffer : public Framebuffer
{
public:
	SSAOFirstPassFramebuffer();
	~SSAOFirstPassFramebuffer();

	/*
		@see Framebuffer::create()
	*/
	void create();

public:
	Texture *depthTexture;
	Texture *normalTexture;
	Texture *colorTexture;
	Texture *specularTexture;
};

