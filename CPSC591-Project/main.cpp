#include "Libraries\glew\glew.h"
#include "Libraries\freeglut\freeglut.h"
#include <math.h>
#include "Scene.h"
#include "Camera.h"
#include "SceneParameters.h"

#define GLM_FORCE_RADIANS

Scene s;

int lastFrameTime = 0;

void mainLoop(void) {
	float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	float dt = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	//std::cout << 1000.0 / dt << std::endl;
	s.renderScene(dt / 1000.0);

	glutSwapBuffers();

	glutPostRedisplay();
}

void mouseMove(int x, int y) {
	int halfWidth = SceneParameters::getScreenWidth() >> 1;
	int halfHeight = SceneParameters::getScreenHeight() >> 1;
	s.getCamera()->processMouseMovement(x - halfWidth, y - halfHeight);

	if (x != halfWidth || y != halfHeight) {
		glutWarpPointer(halfWidth, halfHeight);
	}

	glutPostRedisplay();
}

void mouseMovePassive(int x, int y) {
	int halfWidth = SceneParameters::getScreenWidth() >> 1;
	int halfHeight = SceneParameters::getScreenHeight() >> 1;
	s.getCamera()->processMouseMovement(x - halfWidth, y - halfHeight);

	if (x != halfWidth || y != halfHeight) {
		glutWarpPointer(halfWidth, halfHeight);
	}

	glutPostRedisplay();
}

void pressKey(unsigned char key, int x, int y) {
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

void releaseKey(unsigned char key, int x, int y) {
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
	case 'k':
		s.setShadingTypeNext();
		break;
	case 'p':
		std::cout << s.getCamera()->getPosition().x << " " << s.getCamera()->getPosition().y << " " << s.getCamera()->getPosition().z << std::endl;
		break;
	}
}

int main(int argc, char **argv) {
	SceneParameters::initialize();

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

	//initialize opengl functions
	glewInit();
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	s.initializeScene();

	glutMainLoop();

	return 1;
}