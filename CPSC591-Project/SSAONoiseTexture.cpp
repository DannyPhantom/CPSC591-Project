#include "SSAONoiseTexture.h"
#include "SceneParameters.h"
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
	//define the random number generator
	std::uniform_real_distribution<GLfloat> randomFloats(-1.0, 1.0); // generates random floats between 0 and 1.0
	std::mt19937 MersenneTwisterPRNG(time(0));

	//generate a set of random vectors in the XZ plane (since we rotate the hemisphere samples
	//in XZ plane only
	for (GLuint i = 0; i < noiseDimension * noiseDimension; i++)
	{
		glm::vec3 noiseVec(randomFloats(MersenneTwisterPRNG), 0.0f, randomFloats(MersenneTwisterPRNG));
		noise.push_back(glm::normalize(noiseVec));
	}

	//create the texture and load the data into it
	glGenTextures(1, &textureObj);
	glBindTexture(textureTarget, textureObj);
	glTexImage2D(textureTarget, 0, GL_RGB16F, noiseDimension, noiseDimension, 0, GL_RGB, GL_FLOAT, &noise[0]);
	glTexParameteri(textureTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(textureTarget, 0);
}

glm::vec2 SSAONoiseTexture::getNoiseScale() {
	return glm::vec2(1.0f * SceneParameters::getScreenWidth() / noiseDimension, 1.0f * SceneParameters::getScreenHeight() / noiseDimension);
}