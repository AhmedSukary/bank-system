#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

    string _PrepareLoginRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord = clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(_Password) + Seperator;
        LoginRecord += to_string(_Permissions);
        return LoginRecord;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(
            enMode::UpdateMode,
            vUserData[0],
            vUserData[1],
            vUserData[2],
            vUserData[3],
            vUserData[4],
            clsUtil::DecryptText(vUserData[5]),
            stoi(vUserData[6]));
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string UserRecord = "";
        UserRecord += User.GetFirstName() + Seperator;
        UserRecord += User.GetLastName() + Seperator;
        UserRecord += User.GetEmail() + Seperator;
        UserRecord += User.GetPhone() + Seperator;
        UserRecord += User.GetUserName() + Seperator;
        UserRecord += clsUtil::EncryptText(User.GetPassword()) + Seperator;
        UserRecord += to_string(User.GetPermissions());

        return UserRecord;
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        fstream File;

        File.open("./Bank-System/Bank-System-Data/Users.txt", ios::in); // read Mode
        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                vUsers.push_back(User);
            }
            File.close();
        }
        return vUsers;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {
        fstream File;
        string DataLine;
        File.open("./Bank-System/Bank-System-Data/Users.txt", ios::out); // overwrite

        if (File.is_open())
        {
            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    // we only write records that are not marked for delete.
                    DataLine = _ConverUserObjectToLine(U);
                    File << DataLine << endl;
                }
            }
            File.close();
        }
    }

    void _Update()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.GetUserName() == _UserName)
            {
                U = *this;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream File;
        File.open("./Bank-System/Bank-System-Data/Users.txt", ios::out | ios::app);

        if (File.is_open())
        {
            File << stDataLine << endl;
            File.close();
        }
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enPermissions
    {
        eAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClients = 8,
        pFindClient = 16,
        pTranactions = 32,
        pManageUsers = 64,
        pCurrency = 128,
        pLoginRegister = 256,
    };

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    static stLoginRegisterRecord ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;
        vector<string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);
        return LoginRegisterRecord;
    }

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }

    static clsUser Find(string UserName)
    {
        fstream File;
        File.open("./Bank-System/Bank-System-Data/Users.txt", ios::in); // read Mode

        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {
        fstream File;
        File.open("./Bank-System/Bank-System-Data/Users.txt", ios::in); // read Mode

        if (File.is_open())
        {
            string Line;
            while (getline(File, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
                return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
            break;
        }

        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                // We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
        }
        return enSaveResults::svFaildEmptyObject;
    }

    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector<clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser &U : _vUsers)
        {
            if (U.GetUserName() == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }
        }
        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->_Permissions == enPermissions::eAll)
            return true;

        if ((Permission & this->_Permissions) == Permission)
            return true;
        else
            return false;
    }

    void RegisterLogin()
    {
        string stDateLine = _PrepareLoginRecord();
        fstream File;
        File.open("./Bank-System/Bank-System-Data/LoginRegister.txt", ios::out | ios::app);
        if (File.is_open())
        {
            File << stDateLine << endl;
            File.close();
        }
    }

    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;
        fstream File;
        File.open("./Bank-System/Bank-System-Data/LoginRegister.txt", ios::in); // read Mode
        if (File.is_open())
        {
            string Line;
            stLoginRegisterRecord LoginRegisterRecord;
            while (getline(File, Line))
            {
                LoginRegisterRecord = ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }
            File.close();
        }
        return vLoginRegisterRecord;
    }
};
