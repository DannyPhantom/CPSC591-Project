#include "Scene.h"
#include "ShaderLoader.h"
#include "ObjLoader.h"
#include "SceneParameters.h"
#include "Libraries\glm\gtc\matrix_transform.hpp"
#include <chrono>

Scene::Scene()
{
	shadingType = TYPE_SSAO;
}

Scene::~Scene()
{
}

void Scene::initializeScene() {
	loadShaders();
	loadFramebuffers();
	loadObjects();
	loadOtherStuff();
	placeObjects();
	setupUI();
}

void Scene::renderPhong() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(basicPhongShader);

	glUniformMatrix4fv(glGetUniformLocation(basicPhongShader, "ProjectionMatrix"), 1, false, &(getProjectionMatrix()[0][0]));

	for (SceneObject *obj : objects) {
		obj->draw(basicPhongShader, cam.getViewMatrix());
	}
	//std::cout << "Phong:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
}

void Scene::drawDebug(Texture *t1, Texture *t2, Texture *t3, Texture *t4) {
	TexturedObject2D obj1(t1, glm::vec2(0), 1, 1); obj1.flipY();
	TexturedObject2D obj2(t2, glm::vec2(0), 1, 1); obj2.flipY();
	TexturedObject2D obj3(t3, glm::vec2(0), 1, 1); obj3.flipY();
	TexturedObject2D obj4(t4, glm::vec2(0), 1, 1); obj4.flipY();

	//1
	glViewport(0, 0, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	obj1.draw(shader2D);


	//2
	glViewport(SceneParameters::getScreenWidth() / 2, 0, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	obj2.draw(shader2D);


	//3
	glViewport(0, SceneParameters::getScreenHeight() / 2, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	obj3.draw(shader2D);


	//4
	glViewport(SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	obj4.draw(shader2D);

	glViewport(0, 0, SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight());
}


void Scene::renderSSAO() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	//first pass
	ssaoFirstBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(firstPassSSAOShader);

	glUniformMatrix4fv(glGetUniformLocation(firstPassSSAOShader, "ProjectionMatrix"), 1, false, &(getProjectionMatrix()[0][0]));

	for (SceneObject *obj : objects) {
		obj->draw(firstPassSSAOShader, cam.getViewMatrix());
	}

	ssaoFirstBuffer->unbind();
	//std::cout << "First pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
	

	t1 = std::chrono::high_resolution_clock::now();
	//second pass low freq
	ssaoSecondBufferLowFreq->bind();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(secondPassSSAOShader);

	ssaoFirstBuffer->positionTexture->Bind(GL_TEXTURE0);
	ssaoFirstBuffer->normalTexture->Bind(GL_TEXTURE1);
	ssaoNoiseTex->Bind(GL_TEXTURE2);
	ssaoKernelLowFreq->pushToGPU(secondPassSSAOShader);
	glUniformMatrix4fv(glGetUniformLocation(secondPassSSAOShader, "ProjectionMatrix"), 1, GL_FALSE, &(getProjectionMatrix()[0][0]));
	glUniform1i(glGetUniformLocation(secondPassSSAOShader, "kernelSize"), ssaoKernelLowFreq->getSize());
	glUniform1f(glGetUniformLocation(secondPassSSAOShader, "radius"), 1.0f);
	glUniform2f(glGetUniformLocation(secondPassSSAOShader, "noiseScale"), ssaoNoiseTex->getNoiseScale().x, ssaoNoiseTex->getNoiseScale().y);
	quad->draw();
	ssaoSecondBufferLowFreq->unbind();

	//second pass high freq
	ssaoSecondBufferHighFreq->bind();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(secondPassSSAOShader);

	ssaoFirstBuffer->positionTexture->Bind(GL_TEXTURE0);
	ssaoFirstBuffer->normalTexture->Bind(GL_TEXTURE1);
	ssaoNoiseTex->Bind(GL_TEXTURE2);
	ssaoKernelHighFreq->pushToGPU(secondPassSSAOShader);
	glUniformMatrix4fv(glGetUniformLocation(secondPassSSAOShader, "ProjectionMatrix"), 1, GL_FALSE, &(getProjectionMatrix()[0][0]));
	glUniform1i(glGetUniformLocation(secondPassSSAOShader, "kernelSize"), ssaoKernelHighFreq->getSize());
	glUniform1f(glGetUniformLocation(secondPassSSAOShader, "radius"), 5.0f);
	glUniform2f(glGetUniformLocation(secondPassSSAOShader, "noiseScale"), ssaoNoiseTex->getNoiseScale().x, ssaoNoiseTex->getNoiseScale().y);
	quad->draw();
	ssaoSecondBufferHighFreq->unbind();
	//std::cout << "Second pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;



	t1 = std::chrono::high_resolution_clock::now();
	//third pass
	ssaoThirdBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(thirdPassSSAOShader);
	glUniform1i(glGetUniformLocation(thirdPassSSAOShader, "blurSize"), 4);
	glUniform1i(glGetUniformLocation(thirdPassSSAOShader, "ssaoTextureLowFreq"), 0);
	glUniform1i(glGetUniformLocation(thirdPassSSAOShader, "ssaoTextureHighFreq"), 1);
	ssaoSecondBufferLowFreq->ssaoTexture->Bind(GL_TEXTURE0);
	ssaoSecondBufferHighFreq->ssaoTexture->Bind(GL_TEXTURE1);
	quad->draw();
	ssaoThirdBuffer->unbind();
	//std::cout << "Third pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;




	if (shadingType == TYPE_SSAO) {
		t1 = std::chrono::high_resolution_clock::now();
		//final pass
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(finalPassSSAOShader);

		ssaoFirstBuffer->colorTexture->Bind(GL_TEXTURE0);
		ssaoFirstBuffer->specularTexture->Bind(GL_TEXTURE1);
		ssaoThirdBuffer->blurredSSAOTexture->Bind(GL_TEXTURE2);
		quad->draw();
		ssaoFirstBuffer->colorTexture->unBind(GL_TEXTURE0);
		ssaoFirstBuffer->specularTexture->unBind(GL_TEXTURE1);
		ssaoThirdBuffer->blurredSSAOTexture->unBind(GL_TEXTURE2);
		//std::cout << "Last pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
	}
	else if (shadingType == TYPE_DEBUG) {
		drawDebug(ssaoThirdBuffer->blurredSSAOTexture, ssaoFirstBuffer->normalTexture, ssaoSecondBufferLowFreq->ssaoTexture, ssaoSecondBufferHighFreq->ssaoTexture);
	}
}

void Scene::renderUI() {
	phongShadingButton->render(shader2D);
	SSAOShadingButton->render(shader2D);
	debugShadingButton->render(shader2D);
}

void Scene::renderScene(float dt) {
	cam.update(dt);

	if (shadingType == TYPE_PHONG) {
		renderPhong();
	}
	else if (shadingType == TYPE_SSAO || shadingType == TYPE_DEBUG) {
		renderSSAO();
	}

	drawFPS(dt);
	renderUI();
}

void Scene::drawFPS(float dt) {
	std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
		);

	if (currentTime - lastFPSTime > std::chrono::milliseconds(100)) {
		fpsText->setString(("FPS " + std::to_string((int)floor(1 / dt))));
		lastFPSTime = currentTime;
	}
	fpsText->draw();
}

void Scene::loadFramebuffers() {
	ssaoFirstBuffer = new SSAOFirstPassFramebuffer();
	ssaoFirstBuffer->create();
	ssaoSecondBufferLowFreq = new SSAOSecondPassFramebuffer();
	ssaoSecondBufferLowFreq->create();
	ssaoSecondBufferHighFreq = new SSAOSecondPassFramebuffer();
	ssaoSecondBufferHighFreq->create();
	ssaoThirdBuffer = new SSAOThirdPassFramebuffer();
	ssaoThirdBuffer->create();
}

void Scene::loadShaders() {
	ShaderLoader loader;
	shader2D = loader.loadShader("Shaders/2dshader.vert", "Shaders/2dshader.frag");
	basicPhongShader = loader.loadShader("Shaders/PhongVertexShader.glsl", "Shaders/PhongFragmentShader.glsl");

	firstPassSSAOShader = loader.loadShader("Shaders/SSAOFirstPassVertex.glsl", "Shaders/SSAOFirstPassFragment.glsl");
	glUseProgram(firstPassSSAOShader);
	glUniform1f(glGetUniformLocation(firstPassSSAOShader, "zNear"), SceneParameters::getZNear());
	glUniform1f(glGetUniformLocation(firstPassSSAOShader, "zFar"), SceneParameters::getZFar());

	secondPassSSAOShader = loader.loadShader("Shaders/SSAOSimpleVertex.glsl", "Shaders/SSAOSecondPassFragment.glsl");
	glUseProgram(secondPassSSAOShader);
	glUniform1i(glGetUniformLocation(secondPassSSAOShader, "positionTexture"), 0);
	glUniform1i(glGetUniformLocation(secondPassSSAOShader, "normalTexture"), 1);
	glUniform1i(glGetUniformLocation(secondPassSSAOShader, "noiseTexture"), 2);

	thirdPassSSAOShader = loader.loadShader("Shaders/SSAOSimpleVertex.glsl", "Shaders/SSAOThirdPassFragment.glsl");

	finalPassSSAOShader = loader.loadShader("Shaders/SSAOSimpleVertex.glsl", "Shaders/SSAOLastPassFragment.glsl");
	glUseProgram(finalPassSSAOShader);
	glUniform1i(glGetUniformLocation(finalPassSSAOShader, "colorTexture"), 0);
	glUniform1i(glGetUniformLocation(finalPassSSAOShader, "specularTexture"), 1);
	glUniform1i(glGetUniformLocation(finalPassSSAOShader, "ssaoTexture"), 2);

	glUseProgram(0);
}

void Scene::loadOtherStuff() {
	ssaoKernelLowFreq = new SSAOKernel(64);
	ssaoKernelHighFreq = new SSAOKernel(64);
	ssaoNoiseTex = new SSAONoiseTexture(4);
	quad = new Simple2DQuad();
	fpsText = new Text2D(0, SceneParameters::getScreenHeight() - 65);
	fpsText->setString("FPS");
}

void Scene::loadObjects() {
	ObjLoader loader;
	objects.push_back(loader.loadFromFile("Models/bunny.obj")); 
	objects.push_back(loader.loadFromFile("Models/f16.obj"));
	objects.push_back(loader.loadFromFile("Models/The City.obj"));
	objects.push_back(loader.loadFromFile("Models/Skybox.obj"));
}

void Scene::placeObjects() {
	//bunny
	objects[0]->setPosition(glm::vec3(9, 9, 0));
	objects[0]->setScale(glm::vec3(1, 1, 1));

	//f16
	objects[1]->setPosition(glm::vec3(0, 9, 0));
	objects[1]->setScale(glm::vec3(1, 1, 1));

	//city
	objects[2]->setScale(glm::vec3(0.1, 0.1, 0.1));

	//skybox
	objects[3]->setScale(glm::vec3(0.002, 0.002, 0.002));
	objects[3]->setPosition(glm::vec3(0, -50, 0));
}

void Scene::setupUI() {
	//ssao shading button
	Texture *SSAOShadingButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/SSAOShadingButtonActive.png");
	SSAOShadingButtonTextureActive->Load();
	Texture *SSAOShadingButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/SSAOShadingButtonInactive.png");
	SSAOShadingButtonTextureInactive->Load();
	TexturedObject2D *SSAOShadingButtonTexturedObjectActive = new TexturedObject2D(SSAOShadingButtonTextureActive, glm::vec2(0.68, -0.92), 0.05, 0.04);
	TexturedObject2D *SSAOShadingButtonTexturedObjectInactive = new TexturedObject2D(SSAOShadingButtonTextureInactive, glm::vec2(0.68, -0.92), 0.05, 0.04);
	SSAOShadingButton = new Button(SSAOShadingButtonTexturedObjectInactive, SSAOShadingButtonTexturedObjectActive, this);
	SSAOShadingButton->setClicked(true);

	//phong shading button
	Texture *phongShadingButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/PhongShadingButtonActive.png");
	phongShadingButtonTextureActive->Load();
	Texture *phongShadingButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/PhongShadingButtonInactive.png");
	phongShadingButtonTextureInactive->Load();
	TexturedObject2D *phongShadingButtonTexturedObjectActive = new TexturedObject2D(phongShadingButtonTextureActive, glm::vec2(0.80, -0.92), 0.05, 0.04);
	TexturedObject2D *phongShadingButtonTexturedObjectInactive = new TexturedObject2D(phongShadingButtonTextureInactive, glm::vec2(0.80, -0.92), 0.05, 0.04);
	phongShadingButton = new Button(phongShadingButtonTexturedObjectInactive, phongShadingButtonTexturedObjectActive, this);

	//debug shading button
	Texture *debugShadingButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/DebugShadingButtonActive.png");
	debugShadingButtonTextureActive->Load();
	Texture *debugShadingButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/DebugShadingButtonInactive.png");
	debugShadingButtonTextureInactive->Load();
	TexturedObject2D *debugShadingButtonTexturedObjectActive = new TexturedObject2D(debugShadingButtonTextureActive, glm::vec2(0.92, -0.92), 0.05, 0.04);
	TexturedObject2D *debugShadingButtonTexturedObjectInactive = new TexturedObject2D(debugShadingButtonTextureInactive, glm::vec2(0.92, -0.92), 0.05, 0.04);
	debugShadingButton = new Button(debugShadingButtonTexturedObjectInactive, debugShadingButtonTexturedObjectActive, this);
}

glm::mat4 Scene::getProjectionMatrix() {
	return glm::perspective(
		glm::radians(90.0f),
		1.0f * SceneParameters::getScreenWidth() / SceneParameters::getScreenHeight(),
		SceneParameters::getZNear(),
		SceneParameters::getZFar()
	);
}

void Scene::onButtonClick(Button *button) {
	if (button == phongShadingButton) {
		shadingType = TYPE_PHONG;
		SSAOShadingButton->mouseReleased();
		debugShadingButton->mouseReleased();
	}
	else if (button == SSAOShadingButton) {
		shadingType = TYPE_SSAO;
		phongShadingButton->mouseReleased();
		debugShadingButton->mouseReleased();
	}
	else if (button == debugShadingButton) {
		shadingType = TYPE_DEBUG;
		phongShadingButton->mouseReleased();
		SSAOShadingButton->mouseReleased();
	}
}

void Scene::onButtonRelease(Button *button) {

}


void Scene::onLeftMouseClick(float x, float y) {
	//check for the shading type buttons first
	phongShadingButton->mousePressed(x, y)
		|| SSAOShadingButton->mousePressed(x, y)
		|| debugShadingButton->mousePressed(x, y);
}