// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h"
const int N = 20, M = 15;

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

	private:
		
		int figures[7][4] =
		{
			1,3,5,7, // I
			2,4,5,7, // Z
			3,5,4,6, // S
			3,5,4,7, // T
			2,3,5,7, // L
			3,5,7,6, // J
			2,3,4,5, // O
		};
		struct point
		{
			int x;
			int y;

		} a[4],b[4],c,d;
		int field[N][M] = { 0 };
		string score;
		string next;
		string end;
		int globalScore;
		int hor;
		wstring scoreD;
		int nextT;
		int tetr;
		bool endG;
		bool isFirst;
		bool rotate;
		float fallTimeDelay;
		float fallTime;
		void drawScore();
		bool checkVert(point* r, int x);
		bool checkNew(point x, int r);
		bool checkHor(point* r, int x,int z);
		bool checkRotate(point* r, int x);
		void addNewBlock();
		bool checkLine();
		void deleteLine();
		void lineDelete();
		void drawConsol();
		void generateNext();
	public:
		
		TestApp();
		virtual void KeyPressed(int btnCode);
		virtual void UpdateF(float deltaTime);
		
		
};
