#pragma once
#include <Windows.h>

void gotoxy(int x, int y)
{
	static HANDLE hStdout = NULL;
	COORD coord;

	coord.X = x;
	coord.Y = y;

	if(!hStdout)
	{
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleCursorPosition(hStdout,coord);
}


void textcolor(int c)
{
	static HANDLE hStdout = NULL;
	if(!hStdout)
	{
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	SetConsoleTextAttribute(hStdout,c);
}

void showcursor(bool b)
{
	static HANDLE hStdout = NULL;
	if(!hStdout)
	{
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	CONSOLE_CURSOR_INFO   cursorInfo;
	cursorInfo.dwSize   = 1;
    cursorInfo.bVisible = b;
 
    SetConsoleCursorInfo( hStdout, &cursorInfo );
}

void clrscr(void)
{
	static HANDLE hStdout = NULL;      
	static CONSOLE_SCREEN_BUFFER_INFO csbi;
	const COORD startCoords = {0,0};   
	DWORD dummy;

	if(!hStdout)               
	{
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout,&csbi);
	}

	FillConsoleOutputCharacter(hStdout,
		' ',
		csbi.dwSize.X * csbi.dwSize.Y,
		startCoords,
		&dummy);    
	gotoxy(0,0);
}