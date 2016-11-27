#include "Text2D.h"
#include "Libraries\glm\gtc\type_ptr.hpp"
#include "Libraries\glew\glew.h"
#include <iostream>
#include "SceneParameters.h"

Text2D::Text2D(float xPos, float yPos)
{
	isCenterized = false;
	font = new FTGLPixmapFont("Fonts/OpenSans-Bold.ttf");
	font->FaceSize(fontSize);
	pos = glm::vec2(xPos, yPos);
}


Text2D::~Text2D()
{
	delete font;
}

void Text2D::draw() {
	glUseProgram(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	float red = 1, green = 0, blue = 0, alpha = 1;

	glPixelTransferf(GL_RED_BIAS, red - 1);
	glPixelTransferf(GL_GREEN_BIAS, green - 1);
	glPixelTransferf(GL_BLUE_BIAS, blue - 1);

	font->Render(stringToRender.c_str(), -1, FTPoint(pos.x - xOffset / 2, pos.y - yOffset / 2, 0));
	glPopAttrib();
}


void Text2D::setString(std::string toRender) {
	stringToRender = toRender;
	if (isCenterized) {
		xOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().X() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().X();
		yOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().Y() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().Y();
	}
}

void Text2D::setString(const char *toRender) {
	setString(std::string(toRender));
}


void Text2D::centerize(bool centerize) {
	isCenterized = centerize;

	if (centerize) {
		xOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().X() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().X();
		yOffset = font->BBox(stringToRender.c_str(), -1, FTPoint()).Upper().Y() - font->BBox(stringToRender.c_str(), -1, FTPoint()).Lower().Y();
	}
	else {
		xOffset = 0;
		yOffset = 0;
	}
}