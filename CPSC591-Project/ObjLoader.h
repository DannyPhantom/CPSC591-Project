#pragma once

#include "Libraries\assimp\scene.h"
#include "Libraries\assimp\Importer.hpp"
#include "Libraries\assimp\postprocess.h"
#include "Libraries\assimp\vector3.h"
#include "Libraries\assimp\vector2.h"
#include "Libraries\assimp\material.h"
#include "Libraries\glew\glew.h"
#include "Libraries\glm\vec3.hpp"
#include "Libraries\glm\vec2.hpp"
#include "Texture.h"
#include "SceneObject.h"
#include <iostream>
#include <string>

class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();
	SceneObject *loadFromFile(const char* fileName);
	SceneObject *loadFromFile(std::string fileName);

private:
	std::string directory;

	SceneObject *processScene(const aiScene *scene);
};

