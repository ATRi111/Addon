#pragma once
#include<Windows.h>

struct ConsoleUtility
{
	static HWND ConsoleWindow;
	static int DefaultColor;
	static HANDLE OutputHandle;
	static void SetColor(int color);
	static void DisableWindowResize();
};