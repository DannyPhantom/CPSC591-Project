#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\glm.hpp"
#include <vector>


/*
	Represents a kernel for the SSAO,
	i.e. the samples within a hemisphere
*/
class SSAOKernel
{
public:
	SSAOKernel(int kernelSize);
	~SSAOKernel();

	/*
		Pushes the data into the GPU
	*/
	void pushToGPU(GLuint program);

	/*
		Returns the size of the kernel
	*/
	int getSize();

	/*
		Sets the size of the kernel.
		This will regenerate the samples.
	*/
	void setSize(int size);

private:
	/*
		Generates the samples
	*/
	void generate();


	std::vector<glm::vec3> kernel;				//kernel samples
	int kernelSize;								//size of the kernel, i.e. number of samples
};

