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
	//clear out the current samples
	kernel.clear();

	//create a random number generator
	std::uniform_real_distribution<GLfloat> randomFloats(-1.0, 1.0); // generates random floats between -1.0 and 1.0
	std::mt19937 MersenneTwisterPRNG(time(0));
	
	//generate the samples one by one
	for (int i = 0; i < kernelSize; ++i)
	{
		//create the sample within a hemisphere that points up in the Y direction, and can point any direction in the XZ plane
		glm::vec3 sample(randomFloats(MersenneTwisterPRNG), randomFloats(MersenneTwisterPRNG) * 0.5 + 0.5, randomFloats(MersenneTwisterPRNG));

		//normalize the sample (now it's ON the actual hemisphere, i.e. on its bounds)
		sample = glm::normalize(sample);

		//now scale the sample to be randomply distributed within the hemisphere (this makes an even distribution)
		sample = sample * (randomFloats(MersenneTwisterPRNG) * 0.5f + 0.5f);

		// Scale samples s.t. they're more aligned to center of kernel
		GLfloat scale = (GLfloat)i / (GLfloat)kernelSize;
		scale = 0.1f + 0.9f * scale * scale;
		sample *= scale;

		//store the sample
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