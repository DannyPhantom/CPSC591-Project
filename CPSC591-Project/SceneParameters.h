#pragma once
class SceneParameters
{
public:
	static void initialize();
	static int getScreenHeight();
	static int getScreenWidth();

private:
	SceneParameters();
	~SceneParameters();

private:
	static int screenHeight;
	static int screenWidth;
	static bool isFullScreen;
};

