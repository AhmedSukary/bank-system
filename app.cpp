#include <iostream>
#include "Bank-System/Bank-System-Screens/Login-Screens/clsLoginScreen.h"

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    return 0;
}