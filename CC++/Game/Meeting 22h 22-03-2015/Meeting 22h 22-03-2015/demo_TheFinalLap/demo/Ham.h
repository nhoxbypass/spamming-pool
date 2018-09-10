#pragma once
#include "game.h"

void XoaManHinh();
void DiChuyen_Xuong (toado vatcan[], int &Nvatcan, toado tien[], int &Ntien);
void DieuKhien_Xe (toado &xe);

void Tao_VatCan (int &ThoiGian_tao_VatCan, int MAX, toado vatcan[], int &Nvatcan);
void Tao_Tien (int &ThoiGian_tao_Tien, int MAX, toado tien[], int &Ntien);

int Va_Cham (toado xe, toado mang[], int N, int dodai, int dorong);
void An_Tien (toado xe, toado tien[], int &Ntien);
int GameOver (toado xe, toado vatcan[], int Nvatcan);