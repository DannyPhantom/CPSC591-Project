#pragma once

#include "Libraries\glew\glew.h"
#include "Libraries\glm\glm.hpp"
#include <vector>

class SSAOKernel
{
public:
	SSAOKernel(int kernelSize);
	~SSAOKernel();

	void pushToGPU(GLuint program);
	int getSize();
private:
	void generate();


	std::vector<glm::vec3> kernel;
	int kernelSize;
};

