#pragma once

#include "Framebuffer.h"
#include "Texture.h"

class SSAOSecondPassFramebuffer : public Framebuffer
{
public:
	SSAOSecondPassFramebuffer();
	~SSAOSecondPassFramebuffer();

	void create();

public:
	Texture *ssaoTexture;
};

