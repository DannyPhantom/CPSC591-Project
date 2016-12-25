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
#include "SSAOUI.h"
#include "DynamicObjectCreationUI.h"
#include <chrono>
#include <string>
#include "ObjectToCameraSnapper.h"

/*
	The main class of the program.
	Contains all the UI's, objects, basic controls, etc.
*/
class Scene : public ButtonCallback
{
public:
	Scene();
	~Scene();

	/*
		Initializes the scene
	*/
	void initializeScene();

	/*
		Renders the scene
	*/
	void renderScene(float dt);

	/*
		Returns the scene's camera (controlled by the user)
	*/
	Camera *getCamera() { return &cam; }

	/*
		Calls appropriate triggers when a left mouse click occurres when in UI mode
	*/
	void onLeftMouseClick(float x, float y);

	/*
		Calls appropriate triggers when a left mouse click occurres when in move mode
		In particlar, if there is an object that is currently snapped,
		it will be placed in the scene
	*/
	void onLeftMouseClickMoveMode();

	/*
		Calls appropriate triggers when a left mouse release occurres
	*/
	void onLeftMouseRelease();

	/*
		Calls appropriate triggers when mouse movement happens
	*/
	void onMouseMove(float x, float y);

	/*
		Calls appropriate triggers when a mouse scroll up happens
		In particular, if there is an object that is currently snapped,
		it will increase its size
	*/
	void onWheelScrollUp();

	/*
		Calls appropriate triggers when a mouse scroll down happens
		In particular, if there is an object that is currently snapped,
		it will decrease its size
	*/
	void onWheelScrollDown();

	/*
		Deletes the last object that was placed in the scene (if any).
		This will not delete the skybox and the city
	*/
	void deleteLastObject();

	//ButtonCallback implementation
	void onButtonClick(Button *button);
	void onButtonRelease(Button *button);

private:
	/*
		Loads the framebuffers
	*/
	void loadFramebuffers();

	/*
		Loads all the shaders
	*/
	void loadShaders();
	
	/*
		Loads all the objects
	*/
	void loadObjects();

	/*
		Loads some various stuff such as
		ssao kernel, ssao noise texture,
		etc.
	*/
	void loadOtherStuff();
	
	/*
		Loads and sets up the UI
	*/
	void setupUI();
	
	/*
		Places all the objects in the scene, i.e.
		assigns the position and scales for the skybox and
		the city
	*/
	void placeObjects();

	/*
		Returns the projection matrix for the scene
	*/
	glm::mat4 getProjectionMatrix();

	/*
		Returns the inverse projection matrix for the scene
	*/
	glm::mat4 getInverseProjectionMatrix();

	/*
		Renders the scene using phong shading
	*/
	void renderPhong();

	/*
		Renders the scene using SSAO
	*/
	void renderSSAO();

	/*
		Renders the UI
	*/
	void renderUI();

	/*
		Adds an object to the scene if the user requested for one
		(using the UI)
	*/
	void addDynamicObject();
	
	/*
		Draws the FPS to the screen
	*/
	void drawFPS(float dt);

	/*
		Draws the scene in debug mode. This will draw
		the two SSAO steps, their combined and blurred version
		and the normal texture
	*/
	void drawDebug(Texture *t1, Texture *t2, Texture *t3, Texture *t4);

private:
	std::vector<SceneObject *> objects;
	std::vector<SceneObject *> objectsToRender;

	glm::mat4 projectionMatrix;
	glm::mat4 inverseProjectionMatrix;

	//shaders
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
	SSAOUI *ssaoUI;
	DynamicObjectCreationUI *objCreationUI;

	//Snapper
	ObjectToCameraSnapper *snapper;
};

