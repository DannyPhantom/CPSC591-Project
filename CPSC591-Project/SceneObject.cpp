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

void SceneObject::draw(GLuint program, glm::mat4 viewMatrix)
{
	glUniform1i(glGetUniformLocation(program, "TextureUniform"), 0);
	glm::mat4 mvMatrix = viewMatrix * modelMatrix;
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(mvMatrix)));
	glUniformMatrix4fv(glGetUniformLocation(program, "ModelViewMatrix"), 1, false, &mvMatrix[0][0]);
	glUniformMatrix3fv(glGetUniformLocation(program, "NormalMatrix"), 1, false, &normalMatrix[0][0]);

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