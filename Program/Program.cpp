#include "Program.h"

int main() 
{
    ConsoleUtility::DisableWindowResize();
    ConsoleUtility::SetColor(FOREGROUND_BLUE| BACKGROUND_RED);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++) 
        {
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    ConsoleUtility::SetColor(ConsoleUtility::DefaultColor);
    return 0;
}