#pragma once
#include "TexturedObject2D.h"
#include "Libraries\glew\glew.h"
#include "TrackBar.h"
#include "Button.h"
#include "ButtonCallback.h"

class SSAOUI : public ButtonCallback
{
public:
	SSAOUI(GLuint program);
	~SSAOUI();

	void draw();
	bool mousePressed(float x, float y);
	void mouseReleased();
	void mouseMoved(float newX, float newY);

	int getFirstPassNumberOfSamples();
	float getFirstPassRadius();

	int getSecondPassNumberOfSamples();
	float getSecondPassRadius();

	void setIsHidden(bool isHidden);

private:
	void setup();

private:
	GLuint program;

	TexturedObject2D *background;
	TexturedObject2D *firstPassParamsText;
	TexturedObject2D *firstPassParamsSamplesNumberText;
	TexturedObject2D *firstPassParamsRadiusText;
	TexturedObject2D *secondPassParamsText;
	TexturedObject2D *secondPassParamsSamplesNumberText;
	TexturedObject2D *secondPassParamsRadiusText;
	TexturedObject2D *backgroundHidden;

	TrackBar *firstPassNumberOfSamplesTrackbar;
	TrackBar *firstPassRadiusTrackbar;
	TrackBar *secondPassNumberOfSamplesTrackbar;
	TrackBar *secondPassRadiusTrackbar;

	Button *hideButton;
	Button *showButton;

	bool isHidden;

	//ButtonCallback
	void onButtonClick(Button *button);
	void onButtonRelease(Button *button);

};

