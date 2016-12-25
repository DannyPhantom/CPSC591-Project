#ifndef TRACKBAR_H_
#define TRACKBAR_H_

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Libraries/glew/glew.h"

/**
 * Class that represents a trackbar. Each trackbar has one value
 * that can be changed by dragging the slider.
 * It is a rectangle with another rectangle inside it.
 * The inner rectangle represents the range by which the
 * value can be changed. Finally, a small rectangle is drawn on top of
 * everything, and represents the actual value. Value is always
 * clamped to the allowed values.
 */
class TrackBar {

private:
	float minValue, maxValue, currentValue;		//range of possible values and the current value
	float width, height;						//size of the outer box
	glm::vec3 color;							//color of the outer box
	glm::vec2 center;							//center of the box

	GLuint program;								//shader program for the trackbar
	GLuint VAO;									//vao

	bool mouseStuck = false;					//indicates whether the value of this trackbar is being changed ATM

public:
	TrackBar(float minValue, float maxValue, float width, float height, GLuint program);
	virtual ~TrackBar();

	/*
		Sets the current value of the trackar
	*/
	void setCurrentValue(float value);

	/*
		Sets the color of the outer rectangle
	*/
	void setColor(glm::vec3 color);

	/*
		Sets the center position of the trackbar
	*/
	void setCenter(glm::vec2 center);

	/*
		Renders the trackbar to the screen
	*/
	void render();


	/**
	* This function identifies if the mouse click happened on the slider.
	* If so, it is "stuck" to the current trackbar and all the mouse movements
	* will now affect the value of the trackbar
	*/
	bool mousePressed(float x, float y);

	/*
	* This function makes the mouse become unstuck from 
	* the current trackbar, so that any mouse movement
	* leave the trackbar unaffected until it is clicked
	* again
	*/
	void mouseReleased();

	/**
	* When we are "stuck" to the trackbar, then all the mouse movements
	* have to be translated to the new current value for this trackbar
	*/
	void setNewMousePosition(float x, float y);

	/*
		Returns the current value of the trackbar
	*/
	float getCurrentValue();

	/*
		Identifies whether the mouse is stuck to the current
		trackbar
	*/
	bool getMouseStuck();

};

#endif /* TRACKBAR_H_ */
