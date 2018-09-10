#pragma once

#include "MathEx.h"

#define roadWidth		30
#define roadHeight		30

struct HinhDang
{
	char data[3][3];
};


struct VatCan
{
	Vector2 td;			// quy ước: td < 0 tức là chưa xuất hiện vật cản
	HinhDang hd;
};


struct Xe
{
	Vector2 td;
	int mau;
	HinhDang hd;

	int diem;
};

enum GameScene{
	Intro,
	Menu,
	Option,
	Playing,
	Ending,
	Credits, 
	None
};