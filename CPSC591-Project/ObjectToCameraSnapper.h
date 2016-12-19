#pragma once

#include "Camera.h"
#include "SceneObject.h"

class ObjectToCameraSnapper
{
public:
	ObjectToCameraSnapper(Camera *cam);
	~ObjectToCameraSnapper();

	void snapObject(SceneObject *obj);
	void update();
	bool isObjectSnapped();
	SceneObject *getSnappedObject();
	void stopSnapping();

private:
	Camera *cam;
	SceneObject *obj;
};

