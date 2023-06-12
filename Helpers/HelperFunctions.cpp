#include "HelperFunctions.h"

using std::cout;
using std::cin;
using std::endl;

//http://www.cse.yorku.ca/~oz/hash.html
size_t HashPassword(const char* str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++) hash = hash * 33 + c;

	return hash;
}

bool IsLetter(char ch)
{
	return IsLower(ch) || IsUpper(ch);
}

bool IsDigit(char ch)
{
	return ch >= '0' && ch <= '9';
}

bool IsUpper(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

bool IsLower(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

size_t GetDigitsCount(size_t n)
{
	size_t count = 1;
	while ((n /= 10) != 0) count++;
	return count;
}

void ReadMyStringWithGetLine(const MyString& prompt, MyString& string)
{
	cout << prompt;
	cin.ignore();
	GetLine(cin, string);
}

double GetDistance(const Point& a, const Point& b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
