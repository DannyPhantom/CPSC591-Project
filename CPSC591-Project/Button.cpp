#include "Button.h"

Button::Button(TexturedObject2D *buttonNormal, TexturedObject2D *buttonClicked, ButtonCallback *callback) {
	this -> buttonNormal = buttonNormal;
	this -> buttonClicked = buttonClicked;
	currentState = BUTTON_STATE_RELEASED;
	this -> callback = callback;
	isMouseStuck = false;
}

Button::~Button() {

}

void Button::setClicked(bool clicked) {
	if (clicked) {
		currentState = BUTTON_STATE_CLICKED;
	}
	else {
		currentState = BUTTON_STATE_RELEASED;
	}
}

void Button::render(GLuint program2D) {
	if (currentState == BUTTON_STATE_RELEASED) {
		buttonNormal -> draw(program2D);
	} else if (currentState == BUTTON_STATE_CLICKED) {
		buttonClicked -> draw(program2D);
	}
}

bool Button::mousePressed(float x, float y) {
	glm::vec2 pos = buttonNormal -> getPos();
	float height = buttonNormal -> getHeight();
	float width = buttonNormal -> getWidth();

	//if the click happened on the button
	if (x < pos.x + width
			&& x > pos.x - width
			&& -y < pos.y + height
			&& -y > pos.y - height) {
		//then we change the button's state,
		//call the callback and set the mouse to be "stuck"
		isMouseStuck = true;
		currentState = BUTTON_STATE_CLICKED;
		callback -> onButtonClick(this);

		return true;
	} else {
		return false;
	}
}

void Button::mouseReleased() {
	if (isMouseStuck) {
		callback -> onButtonRelease(this);
	}

	isMouseStuck = false;
	currentState = BUTTON_STATE_RELEASED;
}

bool Button::getMouseStuck() {
	return isMouseStuck;
}
