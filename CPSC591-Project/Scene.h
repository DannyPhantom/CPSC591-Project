#pragma once

#include <vector>
#include "SceneObject.h"
#include "Camera.h"
#include "Framebuffer.h"
#include "SSAOFirstPassFramebuffer.h"
#include "SSAOSecondPassFramebuffer.h"
#include "SSAOThirdPassFramebuffer.h"
#include "SSAOKernel.h"
#include "SSAONoiseTexture.h"
#include "Simple2DQuad.h"
#include "Text2D.h"
#include <chrono>

class Scene
{
public:
	Scene();
	~Scene();

	void initializeScene();
	void renderScene(float dt);
	Camera *getCamera() { return &cam; }

	void setShadingTypeNext();

private:
	void loadFramebuffers();
	void loadShaders();
	void loadObjects();
	void loadOtherStuff();
	void placeObjects();
	glm::mat4 getProjectionMatrix();
	void renderPhong();
	void renderSSAO();
	
	void drawFPS(float dt);

private:
	std::vector<SceneObject *> objects;

	GLuint basicPhongShader;
	GLuint firstPassSSAOShader;
	GLuint secondPassSSAOShader;
	GLuint thirdPassSSAOShader;
	GLuint finalPassSSAOShader;
	Camera cam;

	//framebuffers
	SSAOFirstPassFramebuffer *ssaoFirstBuffer;
	SSAOSecondPassFramebuffer *ssaoSecondBuffer;
	SSAOThirdPassFramebuffer *ssaoThirdBuffer;

	//SSAO kernel
	SSAOKernel *ssaoKernel;

	//SSAO noise
	SSAONoiseTexture *ssaoNoiseTex;

	//quad
	Simple2DQuad *quad;

	//FPS
	Text2D *fpsText;
	std::chrono::milliseconds lastFPSTime;

	enum SceneShadingType {
		TYPE_PHONG,
		TYPE_SSAO,
		TYPE_DEBUG,
	} shadingType;
};

