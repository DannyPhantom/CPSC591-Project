#pragma once

#include "FTGL\ftgl.h"
#include "Libraries\glm\glm.hpp"
#include <string>
#define DEFAULT_FONT_SIZE 72

class Text2D
{
private:
	std::string stringToRender;
	float fontSize = DEFAULT_FONT_SIZE;
	bool isCenterized;
	FTGLPixmapFont *font;
	float xOffset = 0;
	float yOffset = 0;
	glm::vec2 pos;

public:
	Text2D(float xPos, float yPos);
	~Text2D();
	void setString(std::string toRender);
	void setString(const char *toRender);
	void centerize(bool centerize);
	void draw();
	void setFontSize(float size) { fontSize = size; font->FaceSize(size); }
	void resetFontSize() { fontSize = DEFAULT_FONT_SIZE; }
};