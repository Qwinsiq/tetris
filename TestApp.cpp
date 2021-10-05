// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once
#include "TestApp.h"
TestApp::TestApp() : Parent(22, 19)
{
	
	fallTime = 0;
	rotate = 0;
	isFirst = 1;
	fallTimeDelay = 0.35f;
	endG = 1;
	c.x = 8;
	c.y = 0;
	hor = 0;
	d.x = M + 2;
	d.y = 5;
	score = "Score";
	next = "Next";
	end = "Game Over";
	globalScore = 0;
	drawConsol();
	generateNext();
	addNewBlock();
}

void TestApp::drawConsol()
{
	for (int i = 0; i < N; i++)
	{
		SetChar(M,i,L'#');
	}
	for (int i = 0; i < 5; i++)
	{
		SetChar(M +2+i, 10, score[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		SetChar(M + 2+i, 3, next[i]);
	}
}
void TestApp::generateNext()
{
	if (isFirst == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			SetChar(b[i].x, b[i].y, L' ');
		}
	}
	isFirst = 0;
	nextT = rand() % 7;
	for (int i = 0; i < 4; i++)
	{
		b[i].x = figures[nextT][i] % 2 + (d.x);
		b[i].y = figures[nextT][i] / 2 + (d.y);
		SetChar(b[i].x, b[i].y, L'#');
	}

}
void TestApp::addNewBlock()
{
	fallTimeDelay = 0.35f;
	fallTime = 0.0f;
	tetr = nextT;
	for (int i = 0; i < 4; i++)
		{
			a[i].x = figures[tetr][i] % 2 + (c.x);
			a[i].y = figures[tetr][i] / 2 + (c.y);
			SetChar(a[i].x, a[i].y, L'#');

		}
	
}
void TestApp::KeyPressed(int btnCode)
{
	if (btnCode == 75) //w
		hor = -1;
	else if (btnCode == 77) //s
		hor = 1;
	else if (btnCode == 72)
		rotate = 1;
	else if (btnCode == 80)
		fallTimeDelay = 0.05f;
}
bool TestApp::checkVert(point* r, int x)
{
	point temp[4];
	for (int i = 0; i < x; i++)
	{
		temp[i] = r[i];
		temp[i].y++;
	}
	for (int i = 0; i < x; i++)
	{
		if (temp[i].y >= N) return 0;
	}
	for (int i = 0; i < x; i++)
	{
		if (field[temp[i].y][temp[i].x] == 1) return  0;
	}
	return 1;
}
bool TestApp::checkHor(point* r, int x, int z)
{
	point temp[4];
	if (z == 1)
	{
		for (int i = 0; i < x; i++)
		{
			temp[i] = r[i];
			temp[i].x--;
		}
		for (int i = 0; i < x; i++)
		{
			if (temp[i].x <0) return 0;
		}
		for (int i = 0; i < x; i++)
		{
			if (field[temp[i].y][temp[i].x] == 1) return  0;
		}
	}
	if (z == 2)
	{
		for (int i = 0; i < x; i++)
		{
			temp[i] = r[i];
			temp[i].x++;
		}
		for (int i = 0; i < x; i++)
		{
			if (temp[i].x >= M) return 0;
		}
		for (int i = 0; i < x; i++)
		{
			if (field[temp[i].y][temp[i].x] == 1) return  0;
		}
	}
	return 1;
}
bool TestApp::checkNew(point x, int r)
{
	int v = 1;
	for (int i = 0; i < 4; i++)
	{
		a[i].x = figures[tetr][i] % 2 + (x.x);
		a[i].y = figures[tetr][i] / 2 + (x.y);
		if (field[a[i].y][a[i].x] == 1) v=0;
	}
	return v;
}
bool TestApp::checkRotate(point* r, int x)
{
	point temp[4];
	point z = r[1];
	for (int i = 0; i < 4; i++)
	{
		temp[i] = r[i];
	}

	for (int i = 0; i < 4; i++)
	{
		int x = temp[i].y - z.y; // y - y0
		int y = temp[i].x - z.x; // x - x0
		temp[i].x = z.x - x;
		temp[i].y = z.y + y;
		if (field[temp[i].y][temp[i].x] == 1 ||
			temp[i].x >= M || temp[i].x < 0 ||
			temp[i].y>=N) return 0;
	}
	return 1;
}
bool TestApp::checkLine()
{
	int x = 0;
	for (int i = N-1; i > 0; i--)
	{
		x = 0;
		for (int j = 0; j <M; j++)
		{
			if (field[i][j])
			{
				x++;
			}
		}
		if (x == M)
			{
				return 1;
			}
	}
	return 0;
}
void TestApp::deleteLine()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			SetChar(j, i, L' ');
		}
	}
	int x = 0;
	for (int i = N-1; i > 0; i--)
	{
		for (int j = 0; j < M; j++)
		{
			if (field[i][j])x++;
		}
		if (x == M)
		{
			for (int j = i; j > 0; j--)
			{
				for (int p = 0; p < M; p++)
				{
					field[j][p] = field[j - 1][p];
				}
			}
		}
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (field[i][j])
				SetChar(j, i, L'#');
		}
	}
}
void TestApp::lineDelete()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			SetChar(j, i, L' ');
		}
	}
	int k = N - 1;
	for (int i = N - 1; i > 0; i--)
	{
		int count = 0;
		for (int j = 0; j < M; j++)
		{
			if (field[i][j])
			{
				count++;
			}
			field[k][j] = field[i][j];
			
		}
		if (count < M) k--;
		if (count == M) globalScore ++;
		
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			
			if(field[i][j]==1)
				SetChar(j, i, L'#');
		}
	}
}
void TestApp::drawScore()
{
	scoreD = to_wstring(globalScore);
	int v = scoreD.length();
	for (int i = 0; i < v; i++)
	{
		SetChar(M + 2+i, 13, scoreD[i]);
	}
}
void TestApp::UpdateF(float deltaTime)
{
		fallTime += deltaTime;
	if (hor != 0)
	{
		if (hor == -1)
		{
			if (checkHor(a, 4, 1))
			{
				for (int i = 0; i < 4; i++)
				{
					SetChar(a[i].x, a[i].y, L' ');
					a[i].x--;
				}
				for (int i = 0; i < 4; i++)
				{
					SetChar(a[i].x, a[i].y, L'#');
				}
			}
		}
		else if (hor == 1)
		{
			if (checkHor(a, 4, 2))
			{
				for (int i = 0; i < 4; i++)
				{
					SetChar(a[i].x, a[i].y, L' ');
					a[i].x++;
				}
				for (int i = 0; i < 4; i++)
				{
					SetChar(a[i].x, a[i].y, L'#');
				}
			}
		}
	}
	if (rotate != 0)
	{
		if (checkRotate(a, 4))
		{
			point p = a[1];
			for (int i = 0; i < 4; i++)
			{
				SetChar(a[i].x, a[i].y, L' ');
				int x = a[i].y - p.y; // y - y0
				int y = a[i].x - p.x; // x - x0
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			for (int i = 0; i < 4; i++)
			{
				SetChar(a[i].x, a[i].y, L'#');
			}
		}
	}
	if (fallTime >= fallTimeDelay)
	{
		fallTime = 0.0f;
		if (checkVert(a, 4))
		{
			for (int i = 0; i < 4; i++)
			{
				SetChar(a[i].x, a[i].y, L' ');
				a[i].y++;
			}
			for (int i = 0; i < 4; i++)
			{
				SetChar(a[i].x, a[i].y, L'#');
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				field[a[i].y][a[i].x] = 1;
			}
			lineDelete();
			drawScore();
			if (checkNew(c, nextT))
			{
				addNewBlock();
				generateNext();
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					SetChar(5 + i, 9, end[i]);
				}
			}
		}
	}
	hor = 0;
	rotate = 0;
}

