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

/*
	Loads an object from a file.
	Uses ASSIMP as its underlying library
*/
class ObjLoader
{
public:
	ObjLoader();
	~ObjLoader();

	/*
		Loads an object from the given file
	*/
	SceneObject *loadFromFile(const char* fileName);

	/*
		Loads an object from the given file
	*/
	SceneObject *loadFromFile(std::string fileName);

private:
	//directory where the file is stored
	std::string directory;

	/*
		Processes the scene retrieved from the file.
	*/
	SceneObject *processScene(const aiScene *scene);
};

