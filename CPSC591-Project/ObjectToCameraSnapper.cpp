#include "ObjectToCameraSnapper.h"



ObjectToCameraSnapper::ObjectToCameraSnapper(Camera *cam) : cam(cam)
{
}


ObjectToCameraSnapper::~ObjectToCameraSnapper()
{
}

void ObjectToCameraSnapper::snapObject(SceneObject *obj) {
	this->obj = obj;
}

void ObjectToCameraSnapper::update() {
	//update position of the snapped object, if one exists
	if (obj != NULL) {
		obj->setPosition(cam->getPosition() + cam->getViewDirection() * 7.0f);
	}
}

bool ObjectToCameraSnapper::isObjectSnapped() {
	return obj != NULL;
}

SceneObject *ObjectToCameraSnapper::getSnappedObject() {
	return obj;
}

void ObjectToCameraSnapper::stopSnapping() {
	obj = NULL;
}