#include "Libraries\glew\glew.h"
#include "Libraries\freeglut\freeglut.h"
#include <math.h>
#include "Scene.h"
#include "Camera.h"
#include "SceneParameters.h"

#define GLM_FORCE_RADIANS

Scene s;

int lastFrameTime = 0;

enum MouseMode {
	MOUSE_MODE_MOVE,
	MOUSE_MODE_UI,
} mouseMode;

void mainLoop(void) {
	float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	float dt = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	s.renderScene(dt / 1000.0);

	glutSwapBuffers();

	glutPostRedisplay();
}

void toggleMouseMode() {
	if (mouseMode == MOUSE_MODE_MOVE) {
		mouseMode = MOUSE_MODE_UI;
		s.getCamera()->setMoveCameraForward(false);
		s.getCamera()->setMoveCameraBackward(false);
		s.getCamera()->setMoveCameraLeft(false);
		s.getCamera()->setMoveCameraRight(false);
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
	else if (mouseMode == MOUSE_MODE_UI) {
		mouseMode = MOUSE_MODE_MOVE;
		glutSetCursor(GLUT_CURSOR_NONE);
	}
}

void mouseMoveAnyway(int x, int y) {
	if (mouseMode == MOUSE_MODE_MOVE) {
		int halfWidth = SceneParameters::getScreenWidth() >> 1;
		int halfHeight = SceneParameters::getScreenHeight() >> 1;
		s.getCamera()->processMouseMovement(x - halfWidth, y - halfHeight);

		if (x != halfWidth || y != halfHeight) {
			glutWarpPointer(halfWidth, halfHeight);
		}
	}
	else {
		s.onMouseMove(2.0f * x / SceneParameters::getScreenWidth() - 1.0f, 2.0f * y / SceneParameters::getScreenHeight() - 1.0f);
	}

	glutPostRedisplay();
}

void mouseMove(int x, int y) {
	mouseMoveAnyway(x, y);
}

void mouseMovePassive(int x, int y) {
	mouseMoveAnyway(x, y);
}

void mouseClick(int button, int state, int x, int y) {
	if (mouseMode == MOUSE_MODE_UI) {
		int screenWidth = SceneParameters::getScreenWidth();
		int screenHeight = SceneParameters::getScreenHeight();

		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s.onLeftMouseClick((float)x / screenWidth * 2 - 1, (float)y / screenHeight * 2 - 1);
		}

		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			s.onLeftMouseRelease();
		}
	}
	else {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s.onLeftMouseClickMoveMode();
		}
		//wheel scroll up
		else if (button == 3) {
			s.onWheelScrollUp();
		}
		//wheel scroll down
		else if (button == 4) {
			s.onWheelScrollDown();
		}
	}
}

void pressKey(unsigned char key, int x, int y) {
	if (mouseMode == MOUSE_MODE_MOVE) {
		switch (key) {
		case 'w':
			s.getCamera()->setMoveCameraForward(true);
			break;
		case 's':
			s.getCamera()->setMoveCameraBackward(true);
			break;
		case 'a':
			s.getCamera()->setMoveCameraLeft(true);
			break;
		case 'd':
			s.getCamera()->setMoveCameraRight(true);
			break;
		}
	}
	
}

void releaseKey(unsigned char key, int x, int y) {
	if (mouseMode == MOUSE_MODE_MOVE) {
		switch (key) {
		case 'w':
			s.getCamera()->setMoveCameraForward(false);
			break;
		case 's':
			s.getCamera()->setMoveCameraBackward(false);
			break;
		case 'a':
			s.getCamera()->setMoveCameraLeft(false);
			break;
		case 'd':
			s.getCamera()->setMoveCameraRight(false);
			break;
		}
	}

	switch (key) {
	case 'm':
		toggleMouseMode();
		break;
	case 127:					//delete button
		s.deleteLastObject();
		break;
	}

}

int main(int argc, char **argv) {
	SceneParameters::initialize();
	mouseMode = MOUSE_MODE_MOVE;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight());
	glutCreateWindow("Global Illumination");
	glutSetCursor(GLUT_CURSOR_NONE);

	glutDisplayFunc(mainLoop);
	glutIdleFunc(mainLoop);

	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);

	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMovePassive);
	glutMouseFunc(mouseClick);

	//initialize opengl functions
	glewInit();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	s.initializeScene();

	glutMainLoop();

	return 1;
}