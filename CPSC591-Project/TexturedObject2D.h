#ifndef TEXTUREDOBJECT2D_H_
#define TEXTUREDOBJECT2D_H_

#include "Texture.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/*
	Class that represents one textured object
	in a 2D world. It is a simple rectangle 
	with one texture and nothing else. 
	This class is useful for drawing UI
*/
class TexturedObject2D {
public:
	TexturedObject2D(Texture *tex, glm::vec2 pos, float width, float height);
	virtual ~TexturedObject2D();

	/*
		Draws the object to the screen
		@param program shader program to use
	*/
	void draw(GLuint program);

	/*
		Sets the texture of the object
		@param tex texture to set
	*/
	void setTexture(Texture *tex);

	/*
		Gets the current position of the object
	*/
	glm::vec2 getPos() {return pos;}

	/*
		Gets the height of the object
	*/
	float getHeight() {return height;}

	/*
		Gets the width of the object
	*/
	float getWidth() {return width;}

	/*
		Flips the y axis for the object.
		In other words, flips the whole picture
	*/
	void flipY();

private:
	Texture *texture;					//texture to use for drawing
	glm::vec2 pos;						//position of the object (center)
	float height, width;				//width and height of the object
	GLuint VAO;							//VAO for the rectangle
	bool yFlipped = false;				//whether the y axis is flipped

	/*
		Generates VAO for the 2D object
	*/
	void generateVAO();
};

#endif /* TEXTUREDOBJECT2D_H_ */
