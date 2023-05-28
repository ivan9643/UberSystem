#include <iostream>
#include "Address.h"

using std::cout;
using std::endl;

Address::Address(const MyString& name, const Point& coordinates)
{
	this->name = name;
	this->coordinates = coordinates;
}

Address::Address(const MyString& name, const MyString& details, const Point& coordinates)
{
	this->name = name;
	this->details = details;
	this->coordinates = coordinates;
}

void Address::SaveToFile(std::ofstream& file) const
{
	name.SaveToFile(file);
	details.SaveToFile(file);
	coordinates.SaveToFile(file);
}

void Address::ReadFromFile(std::ifstream& file)
{
	name.ReadFromFile(file);
	details.ReadFromFile(file);
	coordinates.ReadFromFile(file);
}

void Point::SaveToFile(std::ofstream& file) const
{
	file.write((const char*)&x, sizeof(x));
	file.write((const char*)&y, sizeof(y));
}

void Point::ReadFromFile(std::ifstream& file)
{
	file.read((char*)&x, sizeof(x));
	file.read((char*)&y, sizeof(y));
}