#pragma once
#include "../Utilities/MyString.h"
#include <limits> //this too

template<class T>
void ReadData(const MyString& prompt, T& data)
{
	while (true) {
		cout << prompt << endl;
		cin >> data;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // check if this constant is allowed to use
			cout << "invalid input" << endl;
		}
		else break;
	}
}

void ReadMyStringWithGetLine(const MyString& prompt, MyString& string)
{
	cout << prompt << endl;
	cin.ignore();
	GetLine(cin, string);
}