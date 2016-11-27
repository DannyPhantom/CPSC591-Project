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
	Texture *positionTexture;
	Texture *normalTexture;
	Texture *colorTexture;
	Texture *specularTexture;
	Texture *depthTexture;
};

