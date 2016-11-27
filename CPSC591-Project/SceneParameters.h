#pragma once
class SceneParameters
{
public:
	static void initialize();
	static int getScreenHeight();
	static int getScreenWidth();
	static float getZNear();
	static float getZFar();

private:
	SceneParameters();
	~SceneParameters();

private:
	static int screenHeight;
	static int screenWidth;
	static bool isFullScreen;
	static float zNear;
	static float zFar;
};

