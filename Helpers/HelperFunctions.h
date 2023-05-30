#pragma once
#include "../Utilities/MyString.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

size_t HashPassword(const char* str);
bool IsLetter(char ch);
bool IsDigit(char ch);
bool IsUpper(char ch);
bool IsLower(char ch);
size_t GetDigitsCount(size_t n);
void ReadMyStringWithGetLine(const MyString& prompt, MyString& string);