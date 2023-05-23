#pragma once
#include "MyString.h"
#include <iostream>
#include <limits> //this too

using std::cout;
using std::cin;
using std::endl;

size_t HashPassword(const char* str);
bool IsLetter(char ch);
bool IsDigit(char ch);
bool IsUpper(char ch);
bool IsLower(char ch);
size_t GetDigitsCount(size_t n);

template<class T>
void ReadData(const MyString& prompt, T& data)
{
    while (true) {
	    cout << prompt << endl; 
        cin >> data;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // check if this constant is allowed to use
            cout << "Invalid input. Please try again: ";
        }
        else break;
    }
}