#pragma once

#include "Mesh.h"
#include <vector>
#include "Libraries\glm\mat4x4.hpp"
#include "Libraries\glm\gtx\transform.hpp"

class SceneObject
{
private:
	std::vector<Mesh *> meshes;
	bool vaoSetup = false;
	bool vboSetup = false;
public:

	SceneObject();
	~SceneObject();
	void addMesh(Mesh *mesh) { meshes.push_back(mesh); }
	std::vector<Mesh *> *getMeshes() { return &meshes; }
	void setupVAOs();
	void setupVBOs();
	void draw(GLuint program, glm::mat4 viewMatrix);

	void setPosition(glm::vec3 pos) { position = pos; recalculateModelMatrix(); }
	void setScale(glm::vec3 sc) { scale = sc; recalculateModelMatrix(); }
	void setRotation(glm::vec3 rot) { rotation = rot; recalculateModelMatrix(); }
	void updateRotation(glm::vec3 dr) { rotation += dr; recalculateModelMatrix(); }
	void updatePosition(glm::vec3 dp) { position += dp; recalculateModelMatrix(); }
	void updateScale(glm::vec3 ds) { scale += ds; recalculateModelMatrix(); }

	void recalculateModelMatrix();

private:
	glm::vec3 position, rotation, scale;
	glm::mat4x4 modelMatrix;
};

