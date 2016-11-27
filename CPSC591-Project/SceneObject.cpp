#include "SceneObject.h"

SceneObject::SceneObject()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}


SceneObject::~SceneObject()
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		delete meshes[i];
	}
}


void SceneObject::setupVAOs() {

	if (vaoSetup)
		return;

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes.at(i)->setupVAO();
	}

	vaoSetup = true;

}

void SceneObject::setupVBOs() {

	if (vboSetup)
		return;

	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes.at(i)->setupVBO();
	}

	vboSetup = true;

}

void SceneObject::draw(GLuint program)
{
	glUniform1i(glGetUniformLocation(program, "TextureUniform"), 0);
	glUniformMatrix4fv(glGetUniformLocation(program, "ModelMatrix"), 1, false, &modelMatrix[0][0]);

	for (unsigned int i = 0; i < meshes.size(); i++) {
		Mesh *mesh = meshes.at(i);
		if (mesh->hasTexture()) {
			mesh->getTexture()->Bind(GL_TEXTURE0);
			glUniform1i(glGetUniformLocation(program, "TextureValid"), true);
		}
		else {
			glUniform1i(glGetUniformLocation(program, "TextureValid"), false);
		}
		// Draw mesh
		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		if (mesh->hasTexture()) {
			mesh->getTexture()->unBind(GL_TEXTURE0);
		}
	}
}

void SceneObject::recalculateModelMatrix() {
	glm::mat4x4 translate = glm::translate(glm::mat4x4(), position);
	glm::mat4x4 trx = glm::rotate(translate, rotation.x, glm::vec3(1, 0, 0));
	glm::mat4x4 trxry = glm::rotate(trx, rotation.y, glm::vec3(0, 1, 0));
	glm::mat4x4 trxryrz = glm::rotate(trxry, rotation.z, glm::vec3(0, 0, 1));
	glm::mat4x4 trxryrzs = glm::scale(trxryrz, this->scale);
	modelMatrix = trxryrzs;
}