#ifndef BUTTON_H_
#define BUTTON_H_

#include "TexturedObject2D.h"
#include "ButtonCallback.h"

class Button {
public:

	/*The constructor assumes that both buttons have same position and dimensions*/
	Button(TexturedObject2D *buttonNormal, TexturedObject2D *buttonClicked, ButtonCallback *callback);
	virtual ~Button();

	//renders the button
	void render(GLuint program2D);

	//called when a mouse is pressed in the scene
	//returns true if the mouse is "captured by the button"
	bool mousePressed(float x, float y);

	//called when a mouse is released
	void mouseReleased();

	//determines if the mouse is captured by this button
	bool getMouseStuck();

	void setClicked(bool clicked);

private:
	TexturedObject2D* buttonNormal;
	TexturedObject2D* buttonClicked;
	enum {
		BUTTON_STATE_CLICKED,
		BUTTON_STATE_RELEASED,
	} currentState;
	ButtonCallback *callback;
	bool isMouseStuck;
};

#endif /* BUTTON_H_ */
