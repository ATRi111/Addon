#include "Program.h"

int main() 
{
    ConsoleUtility::DisableWindowResize();
    ConsoleUtility::SetColor(BACKGROUND_RED);

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++) 
        {
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    ConsoleUtility::ResetColor();
    return 0;
}