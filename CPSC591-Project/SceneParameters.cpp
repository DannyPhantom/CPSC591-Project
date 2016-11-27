#include "SceneParameters.h"
#include "Libraries\freeglut\freeglut.h"

int SceneParameters::screenHeight;
int SceneParameters::screenWidth;
bool SceneParameters::isFullScreen;
float SceneParameters::zNear;
float SceneParameters::zFar;

SceneParameters::SceneParameters()
{
}


SceneParameters::~SceneParameters()
{
}

void SceneParameters::initialize() {
	zNear = 0.5f;
	zFar = 500.0f;
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

float SceneParameters::getZNear() {
	return zNear;
}

float SceneParameters::getZFar() {
	return zFar;
}