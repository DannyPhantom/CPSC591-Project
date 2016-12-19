#pragma once
#include "TexturedObject2D.h"
#include "Libraries\glew\glew.h"
#include "TrackBar.h"
#include "Button.h"
#include "ButtonCallback.h"
#include <string>

class DynamicObjectCreationUI : public ButtonCallback
{
public:
	DynamicObjectCreationUI(GLuint program);
	~DynamicObjectCreationUI();

	void draw();
	bool mousePressed(float x, float y);
	void mouseReleased();
	std::string popQueuedObject();

private:
	void setup();

	//ButtonCallback
	void onButtonClick(Button *button);
	void onButtonRelease(Button *button);
private:
	GLuint program;

	Button *addObjectButton;
	Button *addBunny;
	Button *addTeapot;
	Button *addTree;
	Button *addGrass;

	TexturedObject2D *arrow;

	bool isHidden;

	std::string queuedObject;
};

