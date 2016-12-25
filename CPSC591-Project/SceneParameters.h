#pragma once

/*
	Parameters for the scene
*/
class SceneParameters
{
public:
	/*
	Initializes the parameters
	*/
	static void initialize();
	
	/*
		Returns the screen height
	*/
	static int getScreenHeight();

	/*
		Returns the screen width
	*/
	static int getScreenWidth();

	/*
		Returns the near clipping plane
	*/
	static float getZNear();

	/*
		Returns the far clipping plane
	*/
	static float getZFar();

private:
	/*
		No contructor, since all methods are static
	*/
	SceneParameters();
	~SceneParameters();

private:
	static int screenHeight;
	static int screenWidth;
	static bool isFullScreen;
	static float zNear;
	static float zFar;
};

