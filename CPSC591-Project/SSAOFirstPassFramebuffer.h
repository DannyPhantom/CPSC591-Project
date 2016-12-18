#pragma once

#include "Framebuffer.h"
#include "Texture.h"

class SSAOFirstPassFramebuffer : public Framebuffer
{
public:
	SSAOFirstPassFramebuffer();
	~SSAOFirstPassFramebuffer();

	void create();

public:
	Texture *depthTexture;
	Texture *normalTexture;
	Texture *colorTexture;
	Texture *specularTexture;
};

