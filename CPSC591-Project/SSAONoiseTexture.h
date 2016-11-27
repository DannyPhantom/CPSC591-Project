#pragma once

#include "Texture.h"
#include <vector>
#include "Libraries\glm\glm.hpp"

class SSAONoiseTexture : public Texture
{
public:
	SSAONoiseTexture(int noiseDim);
	~SSAONoiseTexture();

	glm::vec2 getNoiseScale();
private:
	void generate();

	std::vector<glm::vec3> noise;
	int noiseDimension;
};

