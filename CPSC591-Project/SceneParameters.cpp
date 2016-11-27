#include "SceneParameters.h"
#include "Libraries\freeglut\freeglut.h"

int SceneParameters::screenHeight;
int SceneParameters::screenWidth;
bool SceneParameters::isFullScreen;

SceneParameters::SceneParameters()
{
}


SceneParameters::~SceneParameters()
{
}

void SceneParameters::initialize() {
	screenHeight = 900;
	screenWidth = 1500;
	isFullScreen = false;





	if (isFullScreen) {
		screenWidth = glutGet(GLUT_WINDOW_WIDTH);
		screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	}
}

int SceneParameters::getScreenHeight() {
	return screenHeight;
}

int SceneParameters::getScreenWidth() {
	return screenWidth;
}
