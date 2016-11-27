#include "SSAONoiseTexture.h"
#include <random>
#include <ctime>

SSAONoiseTexture::SSAONoiseTexture(int noiseDim) : Texture(GL_TEXTURE_2D, 0)
{
	noiseDimension = noiseDim;
	generate();
}


SSAONoiseTexture::~SSAONoiseTexture()
{
}

void SSAONoiseTexture::generate() {
	std::uniform_real_distribution<GLfloat> randomFloats(-1.0, 1.0); // generates random floats between 0 and 1.0
	std::mt19937 MersenneTwisterPRNG(time(0));

	for (GLuint i = 0; i < noiseDimension * noiseDimension; i++)
	{
		glm::vec3 noiseVec(randomFloats(MersenneTwisterPRNG), 0.0f, randomFloats(MersenneTwisterPRNG));
		noise.push_back(glm::normalize(noiseVec));
	}

	glGenTextures(1, &textureObj);
	glBindTexture(textureTarget, textureObj);
	glTexImage2D(textureTarget, 0, GL_RGB16F, noiseDimension, noiseDimension, 0, GL_RGB, GL_FLOAT, &noise[0]);
	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(textureTarget, 0);
}