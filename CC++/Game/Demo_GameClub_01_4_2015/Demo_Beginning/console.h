// basic console functions, collected by Nguyen Trung Thanh
// abcxyz tcIT

#pragma once

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "console.h"

#define ColorCode_Back				0
#define ColorCode_DarkBlue			1
#define ColorCode_DarkGreen			2
#define ColorCode_DarkCyan			3
#define ColorCode_DarkRed			4
#define ColorCode_DarkPink			5
#define ColorCode_DarkYellow		6
#define ColorCode_DarkWhite			7
#define ColorCode_Grey				8
#define ColorCode_Blue				9
#define ColorCode_Green				10
#define ColorCode_Cyan				11
#define ColorCode_Red				12
#define ColorCode_Pink				13
#define ColorCode_Yellow			14
#define ColorCode_White				15
//#define BackColorCode_DarkBlue		16
//#define BackColorCode_DarkGreen		32
//#define BackColorCode_DarkCyan		48
//#define BackColorCode_DarkRed		64
//#define BackColorCode_DarkPink		80
//#define BackColorCode_DarkYellow	96
//#define BackColorCode_DarkWhite		112
//#define BackColorCode_Grey			128
//#define BackColorCode_Blue			144
//#define BackColorCode_Green			160
//#define BackColorCode_Cyan			176
//#define BackColorCode_Red			192
//#define BackColorCode_Pink			208
//#define BackColorCode_Yellow		224
//#define BackColorCode_White			240
#define default_ColorCode		7


#define key_Up		1072
#define key_Down	1080
#define key_Left	1075
#define key_Right	1077
#define key_none	-1


int inputKey();

//-------------------------Screen-------------------------
void clrscr();

//screen: goto [x,y]
void gotoXY(int column, int line);

//screen: get [x]
int whereX();

//screen: get [y]
int whereY();

void TextColor(int color);

void TextColor(int color, int backColor);
//end----------------------Screen----------------------end