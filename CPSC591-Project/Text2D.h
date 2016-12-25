#pragma once

#include "FTGL\ftgl.h"
#include "Libraries\glm\glm.hpp"
#include <string>
#define DEFAULT_FONT_SIZE 72

/*
	Class that represents a 2D text.
	Uses FTGL as the underlying library
*/
class Text2D
{
private:
	std::string stringToRender;					//String to be rendered to screen
	float fontSize = DEFAULT_FONT_SIZE;			//Size of the font
	
	/*
		If this variable is set to true, then
		the pos variable acts as the center of the text box.
		If the variable is set to false, then
		the text will be rendered starting from pos
	*/
	bool isCenterized;

	FTGLPixmapFont *font;						//Font to use
	float xOffset = 0;							//For internal use. Used for centering the font
	float yOffset = 0;							//For internal use. Used for centering the font
	glm::vec2 pos;								//Position of the text box

public:
	Text2D(float xPos, float yPos);
	~Text2D();

	/*
		Sets the string to be rendered
	*/
	void setString(std::string toRender);

	/*
		Sets the string to be rendered
	*/
	void setString(const char *toRender);

	/*
		Sets wheter the text should be cented.
		@see Text2D::isCenterized
	*/
	void centerize(bool centerize);

	/*
		Draws the text to the screen
	*/
	void draw();
	
	/*
	Sets the font size
	*/
	void setFontSize(float size) { fontSize = size; font->FaceSize(size); }

	/*
		Resets the font size to its defaults
	*/
	void resetFontSize() { fontSize = DEFAULT_FONT_SIZE; }
};