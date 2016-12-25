#include "Simple2DQuad.h"



Simple2DQuad::Simple2DQuad()
{
	create();
}


Simple2DQuad::~Simple2DQuad()
{
}

void Simple2DQuad::create() {
	GLfloat verts[] = {
		-1.0f, 1.0f, 0.0f, 
		-1.0f, -1.0f, 0.0f, 
		1.0f, 1.0f, 0.0f, 
		1.0f, -1.0f, 0.0f, 
	};

	GLfloat uvs[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};
	// Create VBO's
	GLuint vboVerts, vboUvs;

	//VBO for verts
	glGenBuffers(1, &vboVerts);
	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts, GL_STATIC_DRAW);

	//VBO for UV's
	glGenBuffers(1, &vboUvs);
	glBindBuffer(GL_ARRAY_BUFFER, vboUvs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), &uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vboVerts);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, vboUvs);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, 0, GL_FALSE,
		(const GLvoid*)0);

	glBindVertexArray(0);
}

void Simple2DQuad::draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}
