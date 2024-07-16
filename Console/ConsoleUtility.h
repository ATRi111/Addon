#pragma once
#include<Windows.h>
#include<iostream>

struct ConsoleUtility
{
	static const char* Block;
	static HWND ConsoleWindow;
	static HANDLE OutputHandle;
	static int DefaultColor;
	static void SetColor(int color);
	static void ResetColor();
	static void DisableWindowResize();
	static void PrintBuffer(int** buffer, int width, int height);
};