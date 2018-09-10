#include "stdafx.h"
#include "Form1.h"

using namespace demoBall;
using namespace System::Drawing::Drawing2D;

int xBall = 0;
int yBall = 200;
int rBall = 50;


System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e)
{
	G = this->CreateGraphics();
}


System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	timer1->Enabled = !timer1->Enabled;
}


System::Void Form1::timer1_Tick(System::Object^  sender, System::EventArgs^  e)
{
	clock_t cur = clock();

	this->G->Clear (Color::White);

	Pen ^pen = gcnew Pen (Color::FromArgb(255, 0, 0, 0), 5);
	SolidBrush ^solidBrush = gcnew SolidBrush (Color::FromArgb(255, 255, 0, 255));
	
	G->FillEllipse (solidBrush, xBall-rBall, yBall + int(rBall * sin((float)cur)), 2*rBall, 2*rBall);
	//G->FillEllipse (solidBrush, xBall-rBall, yBall - rBall, 2*rBall, 2*rBall);
	//G->DrawEllipse (pen, x-r, y-r, 2*r, 2*r);
	
	xBall = (xBall + 15) % 500;

	delete pen;
	delete solidBrush;
}