#pragma once

#include <iostream>
#include "Libraries\glm\gtc\matrix_transform.hpp"
#include "Libraries\glm\glm.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4 getViewMatrix();
	void addAngles(float phi, float theta);
	void processMouseMovement(int dx, int dy);
	void setMoveCameraForward(bool move) { shouldBeMovedForward = move; }
	void setMoveCameraBackward(bool move) { shouldBeMovedBackwards = move; }
	void setMoveCameraLeft(bool move) { shouldBeMovedLeft = move; }
	void setMoveCameraRight(bool move) { shouldBeMovedRight = move; }
	void update(float dt);

	glm::vec3 getPosition();
	glm::vec3 getViewDirection();

private:
	glm::vec3 position;
	glm::vec3 direction;
	float phi;
	float theta;

	bool shouldBeMovedForward;
	bool shouldBeMovedBackwards;
	bool shouldBeMovedLeft;
	bool shouldBeMovedRight;

	float cameraMovementSpeed;
};

