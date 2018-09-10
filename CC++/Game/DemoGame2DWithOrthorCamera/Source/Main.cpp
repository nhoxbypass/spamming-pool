#include <stdio.h>
#include "2DGameFramework\DebugDefine.h"
#include "Game2D.h"

#ifdef Win32
#include "crtdbg.h"
#endif
#ifdef Android
#include <jni.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "2DGameFramework\Global.h"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern "C" {
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_onTouch(JNIEnv * env, jobject obj,  jint id, jfloat x, jfloat y);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_pauseApp(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_resumeApp(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_exitApp(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setResourcePath(JNIEnv * env, jobject obj,jstring path,jobject assetmanager,jstring path2Cache);
};

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
	Game2D* mainGame = Game2D::GetInstance();

	if (!mainGame->IsInit())
	{
		char so[2];
		sprintf(so,"%d",width);
		LOGE(so);
		sprintf(so,"%d",height);
		LOGE(so);
		if(height>width)
		{
			Global::ScreenWidth=height;
			Global::ScreenHeight=width;
		}
		else
		{
			Global::ScreenWidth=width;
			Global::ScreenHeight=height;
		}
		LOGE("INiting!");
		if (mainGame->CreateGame() != 0)
		{
			delete Global::currentCamera;
			Delete(mainGame);
			LOGE("Error!");
			return;
		}
	}
	else
	{
		LOGE("GAME HAS INIT");
	}
	LOGE("ON CHANGE SURFACE");
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_setResourcePath(JNIEnv * env, jobject obj,jstring path, jobject assetmanager,jstring path2Cache)
{
	const char *systemPath = env->GetStringUTFChars(path, JNI_FALSE);

	Global::gameResourceDir=string(systemPath);
	Global::gameResourcePath=Global::gameResourceDir+"Resources/";
	LOGE("SYSTEM PATH:");
	LOGE(Global::gameResourceDir.c_str());
	string path2Res=Global::gameResourcePath;
	path2Res=path2Res+"Res.txt";
	LOGE(path2Res.c_str());
	FILE* out = fopen(path2Res.c_str(), "r");
	if (out)
		LOGE("FILE EXIST");
	else
		LOGE("FILE NOT FOUND");
	env->ReleaseStringUTFChars(path, systemPath);
}



JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_step(JNIEnv * env, jobject obj)
{

	Game2D* mainGame = Game2D::GetInstance();
	mainGame->DrawFrame(0.03f);

}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_pauseApp(JNIEnv * env, jobject obj)
{

	Game2D* mainGame = Game2D::GetInstance();
	mainGame->Pause();

}


JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_resumeApp(JNIEnv * env, jobject obj)
{
	Game2D* mainGame = Game2D::GetInstance();
	mainGame->Resume();
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_exitApp(JNIEnv * env, jobject obj)
{
	LOGE("BEGIN EXIT");
	Game2D* mainGame = Game2D::GetInstance();
	delete Global::currentCamera;
	LOGE("DELETE CAMERA");
	Delete(mainGame);
	LOGE("DELETE GAME");
	Game::CleanMem();
}


void onTouch(int id, float x, float y)
{
	Game2D* mainGame = Game2D::GetInstance();
	mainGame->onTouch(id,x,y);
}

JNIEXPORT void JNICALL Java_com_android_gl2jni_GL2JNILib_onTouch(JNIEnv * env, jobject obj,  jint id, jfloat x,jfloat y)
{
	//LOGE("TOUCH");
	onTouch(id,x,y);
}
#endif

#ifdef Win32
void main(){
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
	Game2D* game=Game2D::GetInstance();
	ESContext esContext;
	if (game->CreateGame(&esContext)!=0)
	{
		Delete(game);
	}
	game->StartGame(&esContext);
	Delete(game);
	Game::CleanMem();
}
#endif