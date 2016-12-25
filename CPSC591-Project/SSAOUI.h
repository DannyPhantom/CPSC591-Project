#pragma once
#include "TexturedObject2D.h"
#include "Libraries\glew\glew.h"
#include "TrackBar.h"
#include "Button.h"
#include "ButtonCallback.h"

/*
	Represents the UI for the SSAO.
	In particular it lets the user
	control number of SSAO passes and 
	radiuses
*/
class SSAOUI : public ButtonCallback
{
public:
	SSAOUI(GLuint program);
	~SSAOUI();

	/*
		Draws the UI to the screen
	*/
	void draw();

	/*
		Method that should be called when a mouse click occurres.
		It identifies if the mouse click happed on any of the 
		UI elements and returns true if it did.
	*/
	bool mousePressed(float x, float y);

	/*
		Method that should be called when a mouse release occurres.
		Tells the trackbars to stop tracking mouse movements
		and the buttons to change their states to inactive
	*/
	void mouseReleased();

	/*
		Method that should be called when the mouse is moved.
		It will let the trackbars to change values when required
	*/
	void mouseMoved(float newX, float newY);

	/*
		Returns the number of samples for the first SSAO pass
	*/
	int getFirstPassNumberOfSamples();

	/*
		Returns the radius for the first SSAO pass
	*/
	float getFirstPassRadius();
	
	/*
		Returns the number of samples for the second SSAO pass
	*/
	int getSecondPassNumberOfSamples();

	/*
		Returns the radius for the second SSAO pass
	*/
	float getSecondPassRadius();

	/*
		Hides or shows the UI
	*/
	void setIsHidden(bool isHidden);

private:
	/*
		Sets everything up. Creates objects
		and places them in the required positions
	*/
	void setup();

private:
	GLuint program;													//program used to render the UI

	TexturedObject2D *background;									//background texture for the UI
	TexturedObject2D *firstPassParamsText;							//"First pass parameters" Text
	TexturedObject2D *firstPassParamsSamplesNumberText;				//"Number of samples" Text
	TexturedObject2D *firstPassParamsSamplesNumberMinText;			//"8" Text
	TexturedObject2D *firstPassParamsSamplesNumberMaxText;			//"256" Text
	TexturedObject2D *firstPassParamsRadiusText;					//"Radius" Text
	TexturedObject2D *firstPassParamsRadiusMinText;					//"1" Text
	TexturedObject2D *firstPassParamsRadiusMaxText;					//"10" Text
	TexturedObject2D *secondPassParamsText;							//"Second pass parameters" Text
	TexturedObject2D *secondPassParamsSamplesNumberText;			//"Number of samples" Text
	TexturedObject2D *secondPassParamsSamplesNumberMinText;			//"8" Text
	TexturedObject2D *secondPassParamsSamplesNumberMaxText;			//"256" Text
	TexturedObject2D *secondPassParamsRadiusText;					//"Radius" Text
	TexturedObject2D *secondPassParamsRadiusMinText;				//"1" Text
	TexturedObject2D *secondPassParamsRadiusMaxText;				//"10" Text
	TexturedObject2D *backgroundHidden;								//background texture for the UI in its hidden state

	TrackBar *firstPassNumberOfSamplesTrackbar;						//Trackbar for the number of samples for the first pass
	TrackBar *firstPassRadiusTrackbar;								//Trackbar for the radius for the first pass
	TrackBar *secondPassNumberOfSamplesTrackbar;					//Trackbar for the number of samples for second pass
	TrackBar *secondPassRadiusTrackbar;								//Trackbar for the radius for the second pass

	Button *hideButton;												//Hide button
	Button *showButton;												//Show button

	bool isHidden;													//Whether the UI is hidden

	//ButtonCallback
	void onButtonClick(Button *button);
	void onButtonRelease(Button *button);

};

