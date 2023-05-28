#pragma once
#include <fstream>
#include "../Utilities/MyString.h"

struct Point {
	int x = 0;
	int y = 0;
	//def constr
	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};

struct Address {
	MyString name;
	MyString details;
	Point coordinates;

	Address() = default;
	Address(const MyString& name, const Point& coordinates);
	Address(const MyString& name, const MyString& details, const Point& coordinates);

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};