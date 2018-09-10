#pragma once
#include <string>
#include "BaseCamera.h"
#include "Camera.h"
#include "Shader.h"

#define g 10.0f
#define giatoc 0.5f
//#define Android

using namespace std;

class Global
{
public:
	static BaseCamera* currentCamera;
	static int ScreenWidth;
	static int ScreenHeight;
	static string Path2Resource;
	static string gameResourceDir;
	static string gameResourcePath;
	static Shaders* BoundShader;
	static Shaders* TextShader;
};


