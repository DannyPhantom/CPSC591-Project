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
	std::cout << "Phong:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
}

void draw(Texture *t1, Texture *t2, Texture *t3, Texture *t4) {
	glUseProgram(0);
	glClear(GL_COLOR_BUFFER_BIT);


	//1
	glViewport(0, 0, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	t1->Bind(GL_TEXTURE0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(1, 0); glVertex2f(1, -1);
	glTexCoord2f(1, 1); glVertex2f(1, 1);
	glTexCoord2f(0, 1); glVertex2f(-1, 1);
	glEnd();
	t1->unBind(GL_TEXTURE0);


	//2
	glViewport(SceneParameters::getScreenWidth() / 2, 0, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	t2->Bind(GL_TEXTURE0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(1, 0); glVertex2f(1, -1);
	glTexCoord2f(1, 1); glVertex2f(1, 1);
	glTexCoord2f(0, 1); glVertex2f(-1, 1);
	glEnd();
	t2->unBind(GL_TEXTURE0);


	//3
	glViewport(0, SceneParameters::getScreenHeight() / 2, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	t3->Bind(GL_TEXTURE0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(1, 0); glVertex2f(1, -1);
	glTexCoord2f(1, 1); glVertex2f(1, 1);
	glTexCoord2f(0, 1); glVertex2f(-1, 1);
	glEnd();
	t3->unBind(GL_TEXTURE0);


	//4
	glViewport(SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2, SceneParameters::getScreenWidth() / 2, SceneParameters::getScreenHeight() / 2);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	t4->Bind(GL_TEXTURE0);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1, -1);
	glTexCoord2f(1, 0); glVertex2f(1, -1);
	glTexCoord2f(1, 1); glVertex2f(1, 1);
	glTexCoord2f(0, 1); glVertex2f(-1, 1);
	glEnd();
	t4->unBind(GL_TEXTURE0);

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
	std::cout << "First pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
	

	t1 = std::chrono::high_resolution_clock::now();
	//second pass
	ssaoSecondBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(secondPassSSAOShader);

	ssaoFirstBuffer->positionTexture->Bind(GL_TEXTURE0);
	ssaoFirstBuffer->normalTexture->Bind(GL_TEXTURE1); 
	ssaoNoiseTex->Bind(GL_TEXTURE2);
	ssaoKernel->pushToGPU(secondPassSSAOShader);
	glUniformMatrix4fv(glGetUniformLocation(secondPassSSAOShader, "ProjectionMatrix"), 1, GL_FALSE, &(getProjectionMatrix()[0][0]));
	glUniform1i(glGetUniformLocation(secondPassSSAOShader, "kernelSize"), ssaoKernel->getSize());
	glUniform1f(glGetUniformLocation(secondPassSSAOShader, "radius"), 1.0f);
	glUniform2f(glGetUniformLocation(secondPassSSAOShader, "noiseScale"), ssaoNoiseTex->getNoiseScale().x, ssaoNoiseTex->getNoiseScale().y);
	quad->draw();
	ssaoSecondBuffer->unbind();
	std::cout << "Second pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;



	t1 = std::chrono::high_resolution_clock::now();
	//third pass
	ssaoThirdBuffer->bind();
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(thirdPassSSAOShader);
	glUniform1i(glGetUniformLocation(thirdPassSSAOShader, "blurSize"), 4);
	ssaoSecondBuffer->ssaoTexture->Bind(GL_TEXTURE0);
	quad->draw();
	ssaoThirdBuffer->unbind();
	std::cout << "Third pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;




	if (shadingType == TYPE_SSAO) {
		t1 = std::chrono::high_resolution_clock::now();
		//final pass
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(finalPassSSAOShader);

		ssaoFirstBuffer->colorTexture->Bind(GL_TEXTURE0);
		ssaoFirstBuffer->specularTexture->Bind(GL_TEXTURE1);
		ssaoThirdBuffer->blurredSSAOTexture->Bind(GL_TEXTURE2);
		quad->draw();
		std::cout << "Last pass:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
	}
	else if (shadingType == TYPE_DEBUG) {
		draw(ssaoFirstBuffer->normalTexture, ssaoFirstBuffer->positionTexture, ssaoSecondBuffer->ssaoTexture, ssaoThirdBuffer->blurredSSAOTexture);
	}
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
	ssaoSecondBuffer = new SSAOSecondPassFramebuffer();
	ssaoSecondBuffer->create();
	ssaoThirdBuffer = new SSAOThirdPassFramebuffer();
	ssaoThirdBuffer->create();
}

void Scene::loadShaders() {
	ShaderLoader loader;
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
	ssaoKernel = new SSAOKernel(64);
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

glm::mat4 Scene::getProjectionMatrix() {
	return glm::perspective(
		glm::radians(90.0f),
		1.0f * SceneParameters::getScreenWidth() / SceneParameters::getScreenHeight(),
		SceneParameters::getZNear(),
		SceneParameters::getZFar()
	);
}

void Scene::setShadingTypeNext() {
	if (shadingType == TYPE_PHONG) {
		shadingType = TYPE_SSAO;
	}
	else if (shadingType == TYPE_SSAO) {
		shadingType = TYPE_DEBUG;
	}
	else if (shadingType == TYPE_DEBUG) {
		shadingType = TYPE_PHONG;
	}
}