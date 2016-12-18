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
		firstPassParamsSamplesNumberMinText->draw(program);
		firstPassParamsSamplesNumberMaxText->draw(program);
		firstPassParamsRadiusText->draw(program);
		firstPassRadiusTrackbar->render();
		firstPassParamsRadiusMinText->draw(program);
		firstPassParamsRadiusMaxText->draw(program);
		secondPassParamsText->draw(program);
		secondPassParamsSamplesNumberText->draw(program);
		secondPassNumberOfSamplesTrackbar->render();
		secondPassParamsSamplesNumberMinText->draw(program);
		secondPassParamsSamplesNumberMaxText->draw(program);
		secondPassParamsRadiusText->draw(program);
		secondPassRadiusTrackbar->render();
		secondPassParamsRadiusMinText->draw(program);
		secondPassParamsRadiusMaxText->draw(program);
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
	background = new TexturedObject2D(backgroundTexture, glm::vec2(0.75, 0.6), 0.25, 0.4);

	Texture *firstPassParamsTextTexture = new Texture(GL_TEXTURE_2D, "Textures/firstPassParametersText.png");
	firstPassParamsTextTexture->Load();
	firstPassParamsText = new TexturedObject2D(firstPassParamsTextTexture, glm::vec2(0.75, 0.95), 0.2, 0.05);

	Texture *firstPassParamsSamplesNumberTextTexture = new Texture(GL_TEXTURE_2D, "Textures/ssaoParametersSampleNumberText.png");
	firstPassParamsSamplesNumberTextTexture->Load();
	firstPassParamsSamplesNumberText = new TexturedObject2D(firstPassParamsSamplesNumberTextTexture, glm::vec2(0.75, 0.85), 0.1, 0.03);

	firstPassNumberOfSamplesTrackbar = new TrackBar(8, 256, 0.17, 0.015, program);
	firstPassNumberOfSamplesTrackbar->setCenter(glm::vec2(0.75, 0.8));
	firstPassNumberOfSamplesTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	firstPassNumberOfSamplesTrackbar->setCurrentValue(64);

	Texture *firstPassParamsSamplesNumberMinTextTexture = new Texture(GL_TEXTURE_2D, "Textures/8.png");
	firstPassParamsSamplesNumberMinTextTexture->Load();
	firstPassParamsSamplesNumberMinText = new TexturedObject2D(firstPassParamsSamplesNumberMinTextTexture, glm::vec2(0.565, 0.8), 0.015, 0.015);

	Texture *firstPassParamsSamplesNumberMaxTextTexture = new Texture(GL_TEXTURE_2D, "Textures/256.png");
	firstPassParamsSamplesNumberMaxTextTexture->Load();
	firstPassParamsSamplesNumberMaxText = new TexturedObject2D(firstPassParamsSamplesNumberMaxTextTexture, glm::vec2(0.95, 0.8), 0.03, 0.015);

	Texture *firstPassParamsRadiusTextTexture = new Texture(GL_TEXTURE_2D, "Textures/radiusText.png");
	firstPassParamsRadiusTextTexture->Load();
	firstPassParamsRadiusText = new TexturedObject2D(firstPassParamsRadiusTextTexture, glm::vec2(0.75, 0.75), 0.04, 0.03);

	firstPassRadiusTrackbar = new TrackBar(1, 10, 0.17, 0.015, program);
	firstPassRadiusTrackbar->setCenter(glm::vec2(0.75, 0.7));
	firstPassRadiusTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	firstPassRadiusTrackbar->setCurrentValue(1);

	Texture *firstPassParamsRadiusMinTextTexture = new Texture(GL_TEXTURE_2D, "Textures/1.png");
	firstPassParamsRadiusMinTextTexture->Load();
	firstPassParamsRadiusMinText = new TexturedObject2D(firstPassParamsRadiusMinTextTexture, glm::vec2(0.565, 0.70), 0.015, 0.015);

	Texture *firstPassParamsRadiusMaxTextTexture = new Texture(GL_TEXTURE_2D, "Textures/10.png");
	firstPassParamsRadiusMaxTextTexture->Load();
	firstPassParamsRadiusMaxText = new TexturedObject2D(firstPassParamsRadiusMaxTextTexture, glm::vec2(0.9425, 0.70), 0.022, 0.015);

	Texture *secondPassParamsTextTexture = new Texture(GL_TEXTURE_2D, "Textures/secondPassParametersText.png");
	secondPassParamsTextTexture->Load();
	secondPassParamsText = new TexturedObject2D(secondPassParamsTextTexture, glm::vec2(0.75, 0.60), 0.2, 0.05);

	Texture *secondPassParamsSamplesNumberTextTexture = new Texture(GL_TEXTURE_2D, "Textures/ssaoParametersSampleNumberText.png");
	secondPassParamsSamplesNumberTextTexture->Load();
	secondPassParamsSamplesNumberText = new TexturedObject2D(secondPassParamsSamplesNumberTextTexture, glm::vec2(0.75, 0.50), 0.1, 0.03);

	secondPassNumberOfSamplesTrackbar = new TrackBar(8, 256, 0.17, 0.015, program);
	secondPassNumberOfSamplesTrackbar->setCenter(glm::vec2(0.75, 0.45));
	secondPassNumberOfSamplesTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	secondPassNumberOfSamplesTrackbar->setCurrentValue(64);

	Texture *secondPassParamsSamplesNumberMinTextTexture = new Texture(GL_TEXTURE_2D, "Textures/8.png");
	secondPassParamsSamplesNumberMinTextTexture->Load();
	secondPassParamsSamplesNumberMinText = new TexturedObject2D(secondPassParamsSamplesNumberMinTextTexture, glm::vec2(0.565, 0.45), 0.015, 0.015);

	Texture *secondPassParamsSamplesNumberMaxTextTexture = new Texture(GL_TEXTURE_2D, "Textures/256.png");
	secondPassParamsSamplesNumberMaxTextTexture->Load();
	secondPassParamsSamplesNumberMaxText = new TexturedObject2D(secondPassParamsSamplesNumberMaxTextTexture, glm::vec2(0.95, 0.45), 0.03, 0.015);

	Texture *secondPassParamsRadiusTextTexture = new Texture(GL_TEXTURE_2D, "Textures/radiusText.png");
	secondPassParamsRadiusTextTexture->Load();
	secondPassParamsRadiusText = new TexturedObject2D(secondPassParamsRadiusTextTexture, glm::vec2(0.75, 0.40), 0.04, 0.03);

	secondPassRadiusTrackbar = new TrackBar(1, 10, 0.17, 0.015, program);
	secondPassRadiusTrackbar->setCenter(glm::vec2(0.75, 0.35));
	secondPassRadiusTrackbar->setColor(glm::vec3(0.3, 0.3, 0.3));
	secondPassRadiusTrackbar->setCurrentValue(5);

	Texture *secondPassParamsRadiusMinTextTexture = new Texture(GL_TEXTURE_2D, "Textures/1.png");
	secondPassParamsRadiusMinTextTexture->Load();
	secondPassParamsRadiusMinText = new TexturedObject2D(secondPassParamsRadiusMinTextTexture, glm::vec2(0.565, 0.35), 0.015, 0.015);

	Texture *secondPassParamsRadiusMaxTextTexture = new Texture(GL_TEXTURE_2D, "Textures/10.png");
	secondPassParamsRadiusMaxTextTexture->Load();
	secondPassParamsRadiusMaxText = new TexturedObject2D(secondPassParamsRadiusMaxTextTexture, glm::vec2(0.9425, 0.35), 0.022, 0.015);

	Texture *hideButtonTextureActive = new Texture(GL_TEXTURE_2D, "Textures/hideButtonActive.png");
	hideButtonTextureActive->Load();
	Texture *hideButtonTextureInactive = new Texture(GL_TEXTURE_2D, "Textures/hideButtonInactive.png");
	hideButtonTextureInactive->Load();
	TexturedObject2D *hideButtonTexturedObjectActive = new TexturedObject2D(hideButtonTextureActive, glm::vec2(0.75, 0.27), 0.05, 0.04);
	TexturedObject2D *hideButtonTexturedObjectInactive = new TexturedObject2D(hideButtonTextureInactive, glm::vec2(0.75, 0.27), 0.05, 0.04);
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