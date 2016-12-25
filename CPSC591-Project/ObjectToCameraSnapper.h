#pragma once

#include "Camera.h"
#include "SceneObject.h"

/*
	Allows snapping an object to the camera.
	After the object is snapped to the camera,
	any camera movement will result in object's movement as well.
	Snapped object is always placed in front of the camera at a certain
	distance (it is not rotated and\or scaled)
*/
class ObjectToCameraSnapper
{
public:
	ObjectToCameraSnapper(Camera *cam);
	~ObjectToCameraSnapper();

	/*
		Snaps an object to the camera.
		If there was a snapped object already, then
		it will be unsnapped.
	*/
	void snapObject(SceneObject *obj);

	/*
		Updates the object snapped to the camera (if any)
	*/
	void update();
	
	/*
		Identifies whether there is any objects snapped
	*/
	bool isObjectSnapped();

	/*
		Returns the object that if currently snapped to the camera (if any)
	*/
	SceneObject *getSnappedObject();

	/*
		Unattaches the object from the camera
	*/
	void stopSnapping();

private:
	Camera *cam;				//camera to snap objects to 
	SceneObject *obj;			//currently snapped object
};

