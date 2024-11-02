#pragma once
#include <iostream>
#include <iomanip>
#include "../clsScreen.h"
#include "../../Bank-System-Librarys/clsUser.h"
#include "../Main-Menu-Screens/clsMainScreen.h"
#include "../../Bank-System-Librarys/Global.h"

class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFaild = false;
        short FaildLoginCount = 0;

        string Username, Password;
        do
        {
            if (LoginFaild)
            {
                FaildLoginCount++;

                cout << "\nInvlaid Username/Password!\n\n";
                cout << "\n You have " << (3 - FaildLoginCount) << " Trial(s) to login. \n\n";
            }

            if (FaildLoginCount == 3)
            {
                cout << "You are Locked after 3 faild trails \n\n";
                return false;
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();
        } while (LoginFaild);
        
        CurrentUser.RegisterLogin();
        clsMainScreen::ShowMainMenue();
        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();
    }
};
