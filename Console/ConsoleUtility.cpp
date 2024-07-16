#include "ConsoleUtility.h"

HWND ConsoleUtility::ConsoleWindow = GetConsoleWindow();
HANDLE ConsoleUtility::OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int ConsoleUtility::DefaultColor = 15;

void ConsoleUtility::SetColor(int color)
{
	SetConsoleTextAttribute(OutputHandle, color);
}

void ConsoleUtility::DisableWindowResize()
{
	SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_SIZEBOX);
}