#include "SSAOKernel.h"
#include <random>
#include <math.h>
#include <string>
#include <ctime>
#include "Libraries\glew\glew.h"


SSAOKernel::SSAOKernel(int kernelSize)
{
	this->kernelSize = kernelSize;
	generate();
}


SSAOKernel::~SSAOKernel()
{
}

void SSAOKernel::generate() {
	kernel.clear();
	std::uniform_real_distribution<GLfloat> randomFloats(-1.0, 1.0); // generates random floats between -1.0 and 1.0
	std::mt19937 MersenneTwisterPRNG(time(0));
	for (int i = 0; i < kernelSize; ++i)
	{
		glm::vec3 sample(randomFloats(MersenneTwisterPRNG), randomFloats(MersenneTwisterPRNG) * 0.5 + 0.5, randomFloats(MersenneTwisterPRNG));
		sample = glm::normalize(sample);
		sample = sample * (randomFloats(MersenneTwisterPRNG) * 0.5f + 0.5f);
		GLfloat scale = (GLfloat)i / (GLfloat)kernelSize;

		// Scale samples s.t. they're more aligned to center of kernel
		scale = 0.1f + 0.9f * scale * scale;
		//sample *= scale;
		kernel.push_back(sample);
	}
}

void SSAOKernel::pushToGPU(GLuint program) {
	for (int i = 0; i < kernelSize; ++i) {
		glUniform3fv(glGetUniformLocation(program, ("samples[" + std::to_string(i) + "]").c_str()), 1, &kernel[i][0]);
	}
}

int SSAOKernel::getSize() {
	return kernelSize;
}

void SSAOKernel::setSize(int size) {
	if (size != kernelSize) {
		kernelSize = size;
		generate();
	}
}