#include "SSAOUI.h"



SSAOUI::SSAOUI(GLuint program) : program(program)
{
	setup();
	isHidden = false;
}


SSAOUI::~SSAOUI()
{
}

void SSAOUI::draw() {
	if (!isHidden) {
		background->draw(program);
		firstPassParamsText->draw(program);
		firstPassParamsSamplesNumberText->draw(program);
		firstPassNumberOfSamplesTrackbar->render();
		firstPassParamsRadiusText->draw(program);
		firstPassRadiusTrackbar->render();
		secondPassParamsText->draw(program);
		secondPassParamsSamplesNumberText->draw(program);
		secondPassNumberOfSamplesTrackbar->render();
		secondPassParamsRadiusText->draw(program);
		secondPassRadiusTrackbar->render();
		hideButton->render(program);
	}
	else {
		backgroundHidden->draw(program);
		showButton->render(program);
	}
}


void SSAOUI::setup() {
	Texture *backgroundTexture = new Texture(GL_TEXTURE_2D, "Textures/backgroundTexture.png");
	backgroundTexture->Load();
	background = new TexturedObject2D(backgroundTexture, glm::vec2(0.8, 0.6), 0.2, 0.4);

	Texture *firstPassParamsTextTexture = new Texture(GL_TEXTURE_2D, "Textures/firstPassParametersText.png");
	firstPassParamsTextTexture->Load();
	firstPassParamsText = new TexturedObject2D(firstPassParamsTextTexture, glm::vec2(0.8, 0.95), 0.2, 0.05);

	Texture *firstPassParamsSamplesNumberTextTexture = new Texture(GL_TEXTURE_2D, "Textures/ssaoParametersSampleNumberText.png");
	firstPassParamsSamplesNumberTextTexture->Load();
	firstPassParamsSamplesNumberText = new TexturedObject2D(firstPassParamsSamplesNumberTextTexture, glm::vec2(0.8, 0.85), 0.1, 0.03);

	firstPassNumberOfSamplesTrackbar = new TrackBar(8, 256, 0.17, 0.015, program);
	firstPassNumberOfSamplesTrackbar->setCenter(glm::vec2(0.8, 0.8));
	firstPassNumberOfSamplesTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	firstPassNumberOfSamplesTrackbar->setCurrentValue(64);

	Texture *firstPassParamsRadiusTextTexture = new Texture(GL_TEXTURE_2D, "Textures/radiusText.png");
	firstPassParamsRadiusTextTexture->Load();
	firstPassParamsRadiusText = new TexturedObject2D(firstPassParamsRadiusTextTexture, glm::vec2(0.8, 0.75), 0.04, 0.03);

	firstPassRadiusTrackbar = new TrackBar(1, 10, 0.17, 0.015, program);
	firstPassRadiusTrackbar->setCenter(glm::vec2(0.8, 0.7));
	firstPassRadiusTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	firstPassRadiusTrackbar->setCurrentValue(1);

	Texture *secondPassParamsTextTexture = new Texture(GL_TEXTURE_2D, "Textures/secondPassParametersText.png");
	secondPassParamsTextTexture->Load();
	secondPassParamsText = new TexturedObject2D(secondPassParamsTextTexture, glm::vec2(0.8, 0.60), 0.2, 0.05);

	Texture *secondPassParamsSamplesNumberTextTexture = new Texture(GL_TEXTURE_2D, "Textures/ssaoParametersSampleNumberText.png");
	secondPassParamsSamplesNumberTextTexture->Load();
	secondPassParamsSamplesNumberText = new TexturedObject2D(secondPassParamsSamplesNumberTextTexture, glm::vec2(0.8, 0.50), 0.1, 0.03);

	secondPassNumberOfSamplesTrackbar = new TrackBar(8, 256, 0.17, 0.015, program);
	secondPassNumberOfSamplesTrackbar->setCenter(glm::vec2(0.8, 0.45));
	secondPassNumberOfSamplesTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	secondPassNumberOfSamplesTrackbar->setCurrentValue(64);

	Texture *secondPassParamsRadiusTextTexture = new Texture(GL_TEXTURE_2D, "Textures/radiusText.png");
	secondPassParamsRadiusTextTexture->Load();
	secondPassParamsRadiusText = new TexturedObject2D(secondPassParamsRadiusTextTexture, glm::vec2(0.8, 0.40), 0.04, 0.03);

	secondPassRadiusTrackbar = new TrackBar(1, 10, 0.17, 0.015, program);
	secondPassRadiusTrackbar->setCenter(glm::vec2(0.8, 0.35));
	secondPassRadiusTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	secondPassRadiusTrackbar->setCurrentValue(5);

	Texture *hideButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/hideButtonActive.png");
	hideButtonTextureActive->Load();
	Texture *hideButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/hideButtonInactive.png");
	hideButtonTextureInactive->Load();
	TexturedObject2D *hideButtonTexturedObjectActive = new TexturedObject2D(hideButtonTextureActive, glm::vec2(0.8, 0.27), 0.05, 0.04);
	TexturedObject2D *hideButtonTexturedObjectInactive = new TexturedObject2D(hideButtonTextureInactive, glm::vec2(0.8, 0.27), 0.05, 0.04);
	hideButton = new Button(hideButtonTexturedObjectInactive, hideButtonTexturedObjectActive, this);

	Texture *backgroundHiddenTexture = new Texture(GL_TEXTURE_2D, "Textures/backgroundTexture.png");
	backgroundHiddenTexture->Load();
	backgroundHidden = new TexturedObject2D(backgroundHiddenTexture, glm::vec2(0.9, 0.9), 0.1, 0.1);

	Texture *showButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/showButtonActive.png");
	showButtonTextureActive->Load();
	Texture *showButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/showButtonInactive.png");
	showButtonTextureInactive->Load();
	TexturedObject2D *showButtonTexturedObjectActive = new TexturedObject2D(showButtonTextureActive, glm::vec2(0.9, 0.90), 0.05, 0.04);
	TexturedObject2D *showButtonTexturedObjectInactive = new TexturedObject2D(showButtonTextureInactive, glm::vec2(0.9, 0.90), 0.05, 0.04);
	showButton = new Button(showButtonTexturedObjectInactive, showButtonTexturedObjectActive, this);
}

bool SSAOUI::mousePressed(float x, float y) {
	if (!isHidden) {
		return firstPassNumberOfSamplesTrackbar->mousePressed(x, y)
			|| firstPassRadiusTrackbar->mousePressed(x, y)
			|| secondPassNumberOfSamplesTrackbar->mousePressed(x, y)
			|| secondPassRadiusTrackbar->mousePressed(x, y)
			|| hideButton->mousePressed(x, y);
	}
	else {
		return showButton->mousePressed(x, y);
	}
}

void SSAOUI::mouseReleased() {
	firstPassNumberOfSamplesTrackbar->mouseReleased();
	firstPassRadiusTrackbar->mouseReleased();
	secondPassNumberOfSamplesTrackbar->mouseReleased();
	secondPassRadiusTrackbar->mouseReleased();
	hideButton->mouseReleased();
	showButton->mouseReleased();
}

void SSAOUI::mouseMoved(float newX, float newY) {
	firstPassNumberOfSamplesTrackbar->setNewMousePosition(newX, newY);
	firstPassRadiusTrackbar->setNewMousePosition(newX, newY);
	secondPassNumberOfSamplesTrackbar->setNewMousePosition(newX, newY);
	secondPassRadiusTrackbar->setNewMousePosition(newX, newY);
}

int SSAOUI::getFirstPassNumberOfSamples() {
	return (int)floor(firstPassNumberOfSamplesTrackbar->getCurrentValue());
}

float SSAOUI::getFirstPassRadius() {
	return firstPassRadiusTrackbar->getCurrentValue();
}

int SSAOUI::getSecondPassNumberOfSamples() {
	return (int)floor(secondPassNumberOfSamplesTrackbar->getCurrentValue());
}

float SSAOUI::getSecondPassRadius() {
	return secondPassRadiusTrackbar->getCurrentValue();
}

void SSAOUI::setIsHidden(bool isHidden) {
	this->isHidden = isHidden;
}

void SSAOUI::onButtonClick(Button *button) {

}

void SSAOUI::onButtonRelease(Button *button) {
	isHidden = !isHidden;
}