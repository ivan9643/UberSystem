#include <iostream>
#include "Address.h"

using std::cout;
using std::endl;

bool Address::IsNameValid(const MyString& name) const
{
	MyString errorMessage = "address name length must be in [" + MyString(MIN_NAME_LENGTH) + ", " +
		MyString(MAX_NAME_LENGTH) + "]";
	if (name.GetLength() < MIN_NAME_LENGTH) throw std::runtime_error(errorMessage.c_str());
	if (name.GetLength() > MAX_NAME_LENGTH) throw std::runtime_error(errorMessage.c_str());
	return true;
}

bool Address::AreDetailsValid(const MyString& details) const
{
	MyString errorMessage = "address details length must be in [" + MyString(MIN_DETAILS_LENGTH) + ", "
		+ MyString(MAX_DETAILS_LENGTH) + "]";
	if (name.GetLength() < MIN_DETAILS_LENGTH) throw std::runtime_error(errorMessage.c_str());
	if (name.GetLength() > MAX_DETAILS_LENGTH) throw std::runtime_error(errorMessage.c_str());
	return true;
}

Address::Address(const MyString& name, const Point& coordinates)
{
	SetName(name);
	SetCoordinates(coordinates);
}

Address::Address(const MyString& name, const Point& coordinates, const MyString& details)
{
	SetName(name);
	SetCoordinates(coordinates);
	SetDetails(details);
}

const MyString& Address::GetName() const
{
	return name;
}

const MyString& Address::GetDetails() const
{
	return details;
}

const Point& Address::GetCoordinates() const
{
	return coordinates;
}

void Address::SetName(const MyString& name)
{
	if (IsNameValid(name)) this->name = name;
}

void Address::SetDetails(const MyString& details)
{
	if (AreDetailsValid(details)) this->details = details;
}

void Address::SetCoordinates(const Point& coordinates)
{
	this->coordinates = coordinates;
}

void Address::PrintData() const
{
	PrintDataWithoutDetails();
	cout << "   details: " << details << endl;
}

void Address::PrintDataWithoutDetails() const
{
	cout << "   name: " << name << endl;
	cout << "   coordinates: (" << coordinates.x << ", " << coordinates.y << ")" << endl;
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