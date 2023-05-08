#include "Address.h"

Address::Address(const String& name, const String& details, const Point& coordinates)
{
	this->name = name;
	this->details = details;
	this->coodinates = coordinates;
}

void Address::SaveToFile(std::ofstream& file) const
{
	name.SaveToFile(file);
	details.SaveToFile(file);
	coodinates.SaveToFile(file);
}

void Address::ReadFromFile(std::ifstream& file)
{
	name.ReadFromFile(file);
	details.ReadFromFile(file);
	coodinates.ReadFromFile(file);
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