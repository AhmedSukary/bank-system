#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
using namespace std;

class clsString
{
private:
    string _Value;

public:
    clsString()
    {
        _Value = "";
    }

    clsString(string Value)
    {
        _Value = Value;
    }

    void SetValue(string Value)
    {
        _Value = Value;
    }

    string GetValue()
    {
        return _Value;
    }

    static short Length(string txt)
    {
        return txt.length();
    };

    short Length()
    {
        return _Value.length();
    };

    static short CountWords(string txt)
    {
        string delim = " "; // delimiter
        short Counter = 0;
        short pos = 0;

        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = txt.find(delim)) != std::string::npos)
        {
            sWord = txt.substr(0, pos); // store the word
            if (sWord != "")
            {
                Counter++;
            }

            // erase() until positon and move to next word.
            txt.erase(0, pos + delim.length());
        }

        if (txt != "")
        {
            Counter++; // it counts the last word of the string.
        }

        return Counter;
    }

    short CountWords()
    {
        return CountWords(_Value);
    };

    static string UpperFirstLetterOfEachWord(string txt)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < txt.length(); i++)
        {
            if (txt[i] != ' ' && isFirstLetter)
            {
                txt[i] = toupper(txt[i]);
            }

            isFirstLetter = (txt[i] == ' ' ? true : false);
        }

        return txt;
    }

    void UpperFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value
        _Value = UpperFirstLetterOfEachWord(_Value);
    }

    static string LowerFirstLetterOfEachWord(string txt)
    {
        bool isFirstLetter = true;

        for (short i = 0; i < txt.length(); i++)
        {

            if (txt[i] != ' ' && isFirstLetter)
            {
                txt[i] = tolower(txt[i]);
            }

            isFirstLetter = (txt[i] == ' ' ? true : false);
        }

        return txt;
    }

    void LowerFirstLetterOfEachWord()
    {
        // no need to return value , this function will directly update the object value
        _Value = LowerFirstLetterOfEachWord(_Value);
    }

    static string UpperAllString(string txt)
    {
        for (short i = 0; i < txt.length(); i++)
        {
            txt[i] = toupper(txt[i]);
        }
        return txt;
    }

    void UpperAllString()
    {
        _Value = UpperAllString(_Value);
    }

    static string LowerAllString(string txt)
    {
        for (short i = 0; i < txt.length(); i++)
        {
            txt[i] = tolower(txt[i]);
        }
        return txt;
    }

    void LowerAllString()
    {
        _Value = LowerAllString(_Value);
    }

    static char InvertLetterCase(char char1)
    {
        return isupper(char1) ? tolower(char1) : toupper(char1);
    }

    static string InvertAllLettersCase(string txt)
    {
        for (short i = 0; i < txt.length(); i++)
        {
            txt[i] = InvertLetterCase(txt[i]);
        }
        return txt;
    }

    void InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }

    enum enWhatToCount
    {
        SmallLetters = 0,
        CapitalLetters = 1,
        All = 3
    };

    static short CountLetters(string txt, enWhatToCount WhatToCount = enWhatToCount::All)
    {
        if (WhatToCount == enWhatToCount::All)
        {
            return txt.length();
        }

        short Counter = 0;

        for (short i = 0; i < txt.length(); i++)
        {

            if (WhatToCount == enWhatToCount::CapitalLetters && isupper(txt[i]))
                Counter++;

            if (WhatToCount == enWhatToCount::SmallLetters && islower(txt[i]))
                Counter++;
        }

        return Counter;
    }

    static short CountCapitalLetters(string txt)
    {
        short Counter = 0;

        for (short i = 0; i < txt.length(); i++)
        {
            if (isupper(txt[i]))
                Counter++;
        }
        return Counter;
    }

    short CountCapitalLetters()
    {
        return CountCapitalLetters(_Value);
    }

    static short CountSmallLetters(string txt)
    {
        short Counter = 0;

        for (short i = 0; i < txt.length(); i++)
        {

            if (islower(txt[i]))
                Counter++;
        }

        return Counter;
    }

    short CountSmallLetters()
    {
        return CountSmallLetters(_Value);
    }

    static short CountSpecificLetter(string txt, char Letter, bool MatchCase = true)
    {
        short Counter = 0;

        for (short i = 0; i < txt.length(); i++)
        {
            if (MatchCase)
            {
                if (txt[i] == Letter)
                    Counter++;
            }
            else
            {
                if (tolower(txt[i]) == tolower(Letter))
                    Counter++;
            }
        }

        return Counter;
    }

    short CountSpecificLetter(char Letter, bool MatchCase = true)
    {
        return CountSpecificLetter(_Value, Letter, MatchCase);
    }

    static bool IsVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);
        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }

    static short CountVowels(string txt)
    {
        short Counter = 0;
        for (short i = 0; i < txt.length(); i++)
        {
            if (IsVowel(txt[i]))
                Counter++;
        }
        return Counter;
    }

    short CountVowels()
    {
        return CountVowels(_Value);
    }

    static vector<string> Split(string txt, string Delim)
    {
        vector<string> vString;
        short pos = 0;
        string sWord; // define a string variable

        // use find() function to get the position of the delimiters
        while ((pos = txt.find(Delim)) != std::string::npos)
        {
            sWord = txt.substr(0, pos); // store the word
                                       // if (sWord != "")
                                       // {
            vString.push_back(sWord);
            //}

            txt.erase(0, pos + Delim.length()); /* erase() until positon and move to next word. */
        }

        if (txt != "")
        {
            vString.push_back(txt); // it adds last word of the string.
        }

        return vString;
    }

    vector<string> Split(string Delim)
    {
        return Split(_Value, Delim);
    }

    static string TrimLeft(string txt)
    {
        for (short i = 0; i < txt.length(); i++)
        {
            if (txt[i] != ' ')
            {
                return txt.substr(i, txt.length() - i);
            }
        }
        return "";
    }

    void TrimLeft()
    {
        _Value = TrimLeft(_Value);
    }

    static string TrimRight(string txt)
    {
        for (short i = txt.length() - 1; i >= 0; i--)
        {
            if (txt[i] != ' ')
            {
                return txt.substr(0, i + 1);
            }
        }
        return "";
    }

    void TrimRight()
    {
        _Value = TrimRight(_Value);
    }

    static string Trim(string txt)
    {
        return (TrimLeft(TrimRight(txt)));
    }

    void Trim()
    {
        _Value = Trim(_Value);
    }

    static string JoinString(vector<string> vString, string Delim)
    {
        string txt = "";
        for (string &s : vString)
        {
            txt = txt + s + Delim;
        }
        return txt.substr(0, txt.length() - Delim.length());
    }

    static string JoinString(string arrString[], short Length, string Delim)
    {
        string txt = "";

        for (short i = 0; i < Length; i++)
        {
            txt = txt + arrString[i] + Delim;
        }

        return txt.substr(0, txt.length() - Delim.length());
    }

    static string ReverseWordsInString(string txt)
    {
        vector<string> vString;
        string S2 = "";

        vString = Split(txt, " ");

        // declare iterator
        vector<string>::iterator iter = vString.end();

        while (iter != vString.begin())
        {
            --iter;
            S2 += *iter + " ";
        }

        S2 = S2.substr(0, S2.length() - 1); // remove last space.

        return S2;
    }

    void ReverseWordsInString()
    {
        _Value = ReverseWordsInString(_Value);
    }

    static string ReplaceWord(string txt, string StringToReplace, string sRepalceTo, bool MatchCase = true)
    {
        vector<string> vString = Split(txt, " ");

        for (string &s : vString)
        {
            if (MatchCase)
            {
                if (s == StringToReplace)
                {
                    s = sRepalceTo;
                }
            }
            else
            {
                if (LowerAllString(s) == LowerAllString(StringToReplace))
                {
                    s = sRepalceTo;
                }
            }
        }

        return JoinString(vString, " ");
    }

    string ReplaceWord(string StringToReplace, string sRepalceTo)
    {
        return ReplaceWord(_Value, StringToReplace, sRepalceTo);
    }

    static string RemovePunctuations(string txt)
    {
        string S2 = "";

        for (short i = 0; i < txt.length(); i++)
        {
            if (!ispunct(txt[i]))
            {
                S2 += txt[i];
            }
        }

        return S2;
    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }
};