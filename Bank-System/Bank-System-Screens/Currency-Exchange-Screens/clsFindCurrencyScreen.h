#pragma once
#include <iostream>
#include <string>
#include "../clsScreen.h"
#include "../../Bank-System-Librarys/clsCurrency.h"
#include "../../Bank-System-Librarys/clsInputValidate.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();
        cout << "\n_____________________________\n\n";
    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Is Not Found :-(\n";
        }
    }

public:
    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("Find Currency Screen");

        cout << "Find By: [1] Code or [2] Country ? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 2);

        if (Choice == 1)
        {
            cout << "\nPlease Enter Code Name: ";
            clsCurrency Currency = clsCurrency::FindByCode(clsInputValidate::ReadString());
            _ShowResults(Currency);
        }

        if (Choice == 2)
        {
            cout << "\nPlease Enter Country Name: ";
            clsCurrency Currency = clsCurrency::FindByCountry(clsInputValidate::ReadString());
            _ShowResults(Currency);
        }
    }
};