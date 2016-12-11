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
#include "Button.h"
#include "ButtonCallback.h"
#include <chrono>

class Scene : public ButtonCallback
{
public:
	Scene();
	~Scene();

	void initializeScene();
	void renderScene(float dt);
	Camera *getCamera() { return &cam; }

	void onLeftMouseClick(float x, float y);

	//ButtonCallback implementation
	void onButtonClick(Button *button);
	void onButtonRelease(Button *button);

private:
	void loadFramebuffers();
	void loadShaders();
	void loadObjects();
	void loadOtherStuff();
	void setupUI();
	void placeObjects();
	glm::mat4 getProjectionMatrix();
	void renderPhong();
	void renderSSAO();
	void renderUI();
	
	void drawFPS(float dt);
	void drawDebug(Texture *t1, Texture *t2, Texture *t3, Texture *t4);

private:
	std::vector<SceneObject *> objects;

	GLuint basicPhongShader;
	GLuint firstPassSSAOShader;
	GLuint secondPassSSAOShader;
	GLuint thirdPassSSAOShader;
	GLuint finalPassSSAOShader;
	GLuint shader2D;
	Camera cam;

	//framebuffers
	SSAOFirstPassFramebuffer *ssaoFirstBuffer;
	SSAOSecondPassFramebuffer *ssaoSecondBufferLowFreq; 
	SSAOSecondPassFramebuffer *ssaoSecondBufferHighFreq;
	SSAOThirdPassFramebuffer *ssaoThirdBuffer;

	//SSAO kernel
	SSAOKernel *ssaoKernelLowFreq;
	SSAOKernel *ssaoKernelHighFreq;

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

	//UI
	Button *phongShadingButton;
	Button *SSAOShadingButton;
	Button *debugShadingButton;
};

