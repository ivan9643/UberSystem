#pragma once
#include <fstream>
#include "String.h"

struct Point {
	int x = 0;
	int y = 0;
	//def constr
	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};

struct Address {
	String name;
	String details;
	Point coodinates;

	Address() = default;
	Address(const String& name, const String& details, const Point& coordinates);

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};