#pragma once
#include "../Utilities/MyString.h"
#include "../Utilities/MyVector.hpp"
#include "../SmartPointers/SharedPtr.hpp"
#include <limits>

using std::cout;
using std::cin;
using std::endl;

template<class T>
void ReadData(const MyString& prompt, T& data)
{
	while (true) {
		cout << prompt;
		cin >> data;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "invalid input" << endl;
		}
		else break;
	}
}