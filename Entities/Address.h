#pragma once
#include <fstream>
#include "../Utilities/MyString.h"

struct Point {
	int x = 0;
	int y = 0;
};

const size_t MIN_NAME_LENGTH = 3;
const size_t MAX_NAME_LENGTH = 50;
const size_t MIN_DETAILS_LENGTH = 3;
const size_t MAX_DETAILS_LENGTH = 100;

class Address {
	MyString name;
	MyString details;
	Point coordinates;

	bool IsNameValid(const MyString& name) const;
	bool AreDetailsValid(const MyString& details) const;
public:
	Address() = default;
	Address(const MyString& name, const Point& coordinates);
	Address(const MyString& name, const Point& coordinates, const MyString& details);

	const MyString& GetName() const;
	const MyString& GetDetails() const;
	const Point& GetCoordinates() const;

	void SetName(const MyString& name);
	void SetDetails(const MyString& details);
	void SetCoordinates(const Point& coordinates);

	void PrintData() const;
	void PrintDataWithoutDetails() const;
};