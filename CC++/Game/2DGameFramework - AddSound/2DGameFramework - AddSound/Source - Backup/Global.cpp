#include "Global.h"

BaseCamera* Global::currentCamera=new Camera();
string Global::Path2Resource="Resources/Res.txt";
Shaders* Global::BoundShader=new Shaders();
string Global::gameResourceDir="../";
string Global::gameResourcePath="../Resources/";
int Global::ScreenWidth=1076;
int Global::ScreenHeight=720;

