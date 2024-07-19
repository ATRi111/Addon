#include "ConsoleUtility.h"
using namespace std;

const char* ConsoleUtility::Block = "  ";
HWND ConsoleUtility::ConsoleWindow = GetConsoleWindow();
HANDLE ConsoleUtility::OutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
int ConsoleUtility::DefaultColor = 15;

void ConsoleUtility::SetColor(int color)
{
	SetConsoleTextAttribute(OutputHandle, color);
}

void ConsoleUtility::ResetColor()
{
	SetColor(DefaultColor);
}

void ConsoleUtility::DisableWindowResize()
{
	SetWindowLong(ConsoleWindow, GWL_STYLE, GetWindowLong(ConsoleWindow, GWL_STYLE) & ~WS_SIZEBOX);
}

void ConsoleUtility::PrintBuffer(int** buffer, int width, int height)
{
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			SetColor(buffer[x][y]);
			cout << Block;
		}
		ResetColor();
		cout << endl;
	}
}