#pragma once
#include "../Utilities/MyString.h"
#include "../Entities/Address.h"
#include <iostream>

size_t HashPassword(const char* str);
bool IsLetter(char ch);
bool IsDigit(char ch);
bool IsUpper(char ch);
bool IsLower(char ch);
size_t GetDigitsCount(size_t n);
void ReadMyStringWithGetLine(const MyString& prompt, MyString& string);
double GetDistance(const Point& a, const Point& b);