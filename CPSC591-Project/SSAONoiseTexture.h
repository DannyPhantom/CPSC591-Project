#pragma once

#include "Texture.h"
#include <vector>
#include "Libraries\glm\glm.hpp"

/*
	Represents a noise texture for the SSAO.
	It allows to define a random rotation
	for the hemisphere samples
*/
class SSAONoiseTexture : public Texture
{
public:
	SSAONoiseTexture(int noiseDim);
	~SSAONoiseTexture();

	/*
		Returns the noise scale,
		i.e. by how much to move along the 
		texture in each fragment step
	*/
	glm::vec2 getNoiseScale();

private:
	/*
		Generates the noise texture
	*/
	void generate();

	/*
		The noise texture itself, stored in an array
	*/
	std::vector<glm::vec3> noise;

	/*
		The dimension of the texture
		(this number represents only 1 side,
		i.e. the whole texture will be noiseDimension * noiseDimension)
	*/
	int noiseDimension;
};

