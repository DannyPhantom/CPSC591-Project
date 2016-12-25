#include "Libraries\glew\glew.h"
#include "Libraries\freeglut\freeglut.h"
#include <math.h>
#include "Scene.h"
#include "Camera.h"
#include "SceneParameters.h"

#define GLM_FORCE_RADIANS

Scene s;

int lastFrameTime = 0;

/*
	There are 2 mouse modes: the one that lets you move around
	the world and the one that lets you interact with the UI
*/
enum MouseMode {
	MOUSE_MODE_MOVE,
	MOUSE_MODE_UI,
} mouseMode;

/*
	Main program loop.
	Calculates the delta time that's been elapsed for the given frame, 
	calls the main scene method to process everything and draw
	and show it to the screen
*/
void mainLoop(void) {
	//calculate dt
	float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	float dt = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	//render the scene and do other relevant stuff
	s.renderScene(dt / 1000.0);

	//swap buffers
	glutSwapBuffers();

	//ask for another frame right away
	glutPostRedisplay();
}

/*
	Toggles the mouse mode.
	Changes the mouse mode and does appropriate modifications
*/
void toggleMouseMode() {
	//if we are currently moving in the world
	if (mouseMode == MOUSE_MODE_MOVE) {
		mouseMode = MOUSE_MODE_UI;

		//then stop all the movement
		s.getCamera()->setMoveCameraForward(false);
		s.getCamera()->setMoveCameraBackward(false);
		s.getCamera()->setMoveCameraLeft(false);
		s.getCamera()->setMoveCameraRight(false);

		//and show the cursor
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
	}
	//if we are interacting with the UI
	else if (mouseMode == MOUSE_MODE_UI) {
		mouseMode = MOUSE_MODE_MOVE;

		//simply remove the cursor
		glutSetCursor(GLUT_CURSOR_NONE);
	}
}

/*
	Method that is being called on any mouse move
	(either active or passive)
	@param x x position of the mouse
	@param y y position of the mouse
*/
void mouseMoveAnyway(int x, int y) {
	//if we are moving in the world
	if (mouseMode == MOUSE_MODE_MOVE) {
		//then we let the scene process the mouse movement
		//but before we transfer the mouse coordinate from
		//[0, width] and [0, height]
		//to
		//[-width/2, width/2] and [-height/2, height/2]
		//(which is later on transfered to [-1, 1])
		int halfWidth = SceneParameters::getScreenWidth() >> 1;
		int halfHeight = SceneParameters::getScreenHeight() >> 1;
		s.getCamera()->processMouseMovement(x - halfWidth, y - halfHeight);

		//move the pointer to the center of the screen so that we don't have the mouse out there somewhere
		if (x != halfWidth || y != halfHeight) {
			glutWarpPointer(halfWidth, halfHeight);
		}
	}
	//if we are interacting with the UI
	else {
		//transfer the coordinates of the mouse to [-1, 1] and let the scene know about it
		s.onMouseMove(2.0f * x / SceneParameters::getScreenWidth() - 1.0f, 2.0f * y / SceneParameters::getScreenHeight() - 1.0f);
	}

	glutPostRedisplay();
}

/*
	Callback method for the active mouse movement
*/
void mouseMove(int x, int y) {
	mouseMoveAnyway(x, y);
}

/*
	Callback method for the passive mouse movement
*/
void mouseMovePassive(int x, int y) {
	mouseMoveAnyway(x, y);
}

/*
	Callback method for the mouse click
	@param button button that was clicked
	@param state either GLUT_DOWN or GLUT_UP
	@param x x position of the click
	@param y y position of the click
*/
void mouseClick(int button, int state, int x, int y) {
	//if we are interacting with the UI
	if (mouseMode == MOUSE_MODE_UI) {
		int screenWidth = SceneParameters::getScreenWidth();
		int screenHeight = SceneParameters::getScreenHeight();

		//When the left button is clicked, we pass it to the scene
		//in order to process possible button/trackbar clicks
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s.onLeftMouseClick((float)x / screenWidth * 2 - 1, (float)y / screenHeight * 2 - 1);
		}

		//when the left button is released, we pass it to the scene
		//in order to deactivate possible button/trackbar clicks
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			s.onLeftMouseRelease();
		}
	}

	//if we are in the world
	else {
		//when the left mouse button is clicked, we pass
		//it to the scene so that if there are any new objects,
		//they will be placed
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			s.onLeftMouseClickMoveMode();
		}
		//when wheel is scrolled up, we increase the size of
		//the currently held object (if any)
		else if (button == 3) {
			s.onWheelScrollUp();
		}
		//when wheel is scrolled down, we decrease the size of
		//the currently helf object (if any)
		else if (button == 4) {
			s.onWheelScrollDown();
		}
	}
}

/*
	Callback function for any normal keyboard key press
	@param key code of the key pressed
	@param x x position of the mouse at the time of click
	@param y y position of the mouse at the time of click
*/
void pressKey(unsigned char key, int x, int y) {
	if (mouseMode == MOUSE_MODE_MOVE) {
		switch (key) {
		//move forward
		case 'w':
			s.getCamera()->setMoveCameraForward(true);
			break;
		//move backwards
		case 's':
			s.getCamera()->setMoveCameraBackward(true);
			break;
		//move left
		case 'a':
			s.getCamera()->setMoveCameraLeft(true);
			break;
		//move right
		case 'd':
			s.getCamera()->setMoveCameraRight(true);
			break;
		}
	}
	
}

/*
	Callback function for any normal keyboard key release
	@param key code of the key released
	@param x x position of the mouse at the time of release
	@param y y position of the mouse at the time of release
*/
void releaseKey(unsigned char key, int x, int y) {
	if (mouseMode == MOUSE_MODE_MOVE) {
		switch (key) {
		//stop moving forward
		case 'w':
			s.getCamera()->setMoveCameraForward(false);
			break;
		//stop moving backwards
		case 's':
			s.getCamera()->setMoveCameraBackward(false);
			break;
		//stop moving left
		case 'a':
			s.getCamera()->setMoveCameraLeft(false);
			break;
		//stop moving right
		case 'd':
			s.getCamera()->setMoveCameraRight(false);
			break;
		}
	}

	switch (key) {
	//toggle mouse mode
	case 'm':
		toggleMouseMode();
		break;
	//delete last placed object
	case 127:					//delete button
		s.deleteLastObject();
		break;
	}

}

/*
	Entry point.
	Sets everything up
*/
int main(int argc, char **argv) {
	//initialize the scene parameters and
	//set the mouse mode to move
	SceneParameters::initialize();
	mouseMode = MOUSE_MODE_MOVE;

	//initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight());
	glutCreateWindow("Global Illumination");
	glutSetCursor(GLUT_CURSOR_NONE);

	//setup callbacks
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

	//initialize the scene
	s.initializeScene();

	//start the main loop
	glutMainLoop();

	return 1;
}