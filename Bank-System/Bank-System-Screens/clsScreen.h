#pragma once
#include <iostream>
#include "../Bank-System-Librarys/clsUser.h"
#include "../Bank-System-Librarys/clsDate.h"
#include "../Bank-System-Librarys/Global.h"
using namespace std;

class clsScreen
{
protected :
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________";
        cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________\n";
        cout << "\n\t\t\t\t\tUser: " << CurrentUser.GetUserName();
        cout << "\t|    Date: " << clsDate::DateToString(clsDate::GetSystemDate()) << "\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
            if (!CurrentUser.CheckAccessPermission(Permission))
            {
                cout << "\t\t\t\t\t______________________________________";
                cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";   
                cout << "\n\t\t\t\t\t______________________________________\n\n";
                
                cout << "\n\t\t\t\t\tUser:" << CurrentUser.GetUserName() << endl;
                cout << "\t|    Date: " << clsDate::DateToString(clsDate::GetSystemDate()) << "\n\n";
                return false;
            }
            else
            {
                return true;
            }
    }
};