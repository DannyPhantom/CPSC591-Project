#pragma once

#include "Framebuffer.h"
#include "Texture.h"

class SSAOThirdPassFramebuffer : public Framebuffer
{
public:
	SSAOThirdPassFramebuffer();
	~SSAOThirdPassFramebuffer();

	void create();

public:
	Texture *blurredSSAOTexture;
};

