#pragma once
#include "TexturedObject2D.h"
#include "Libraries\glew\glew.h"
#include "TrackBar.h"
#include "Button.h"
#include "ButtonCallback.h"
#include <string>

/*
	Represents the UI for the dynamic object creation.
	In particular it lets the user dynamically add objects
	to the world and then place them wherever
*/
class DynamicObjectCreationUI : public ButtonCallback
{
public:
	DynamicObjectCreationUI(GLuint program);
	~DynamicObjectCreationUI();

	/*
		Draws the UI to the screen
	*/
	void draw();

	/*
		Function that should be called on a mouse press.
		This will let the UI capture clicks that happened
		on any of its buttons
	*/
	bool mousePressed(float x, float y);

	/*
		Function that should b called on a mouse release.
		This will let the UI change states of buttons that 
		were clicked before
	*/
	void mouseReleased();

	/*
		Returns and removes an object (if any)
		that was requested by the user
	*/
	std::string popQueuedObject();

private:
	/*
		Sets the UI up
	*/
	void setup();

	//ButtonCallback
	void onButtonClick(Button *button);
	void onButtonRelease(Button *button);
private:
	GLuint program;					//program used to draw the UI

	Button *addObjectButton;		//"Add object" button
	Button *addBunny;				//"Bunny" button
	Button *addTeapot;				//"Teapot" button
	Button *addTree;				//"Tree" button
	Button *addGrass;				//"Grass" button

	TexturedObject2D *arrow;		//Arrow texture 

	bool isHidden;					//Whether the UI is hidden or expanded

	std::string queuedObject;		//Object that was requested by the user
};

