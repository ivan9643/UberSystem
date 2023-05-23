#include <cstring>
#include <fstream>
#include <iostream>
#include "MyString.h"
#include "HelperFunctions.h"

void MyString::CopyFrom(const MyString& other)
{
	length = other.length;
	data = new char[length + 1];
	strcpy_s(data, length + 1, other.data);
}

void MyString::MoveFrom(MyString&& other)
{
	length = other.length;
	data = other.data;
	other.data = nullptr;
}

void MyString::Free()
{
	delete[] data;
	length = 0;
}

MyString::MyString(const MyString& other)
{
	CopyFrom(other);
}

MyString::MyString(MyString&& other) noexcept
{
	MoveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		Free();
		MoveFrom(std::move(other));
	}
	return *this;
}

char& MyString::operator[](size_t index)
{
	if (index >= length) throw std::runtime_error("index out of range");
	return data[index];
}

const char MyString::operator[](size_t index) const
{
	if (index >= length) throw std::runtime_error("index out of range");
	return data[index];
}

MyString MyString::operator+=(const MyString& other)
{
	length += other.length;
	char* newData = new char[length + 1] {};
	strcat_s(newData, length + 1, data);
	strcat_s(newData, length + 1, other.data);
	delete[] data;
	data = newData;
	return *this;
}

MyString::~MyString()
{
	Free();
}

size_t MyString::GetLength() const
{
	return length;
}

bool MyString::empty() const
{
	return length == 0;
}

void MyString::clear()
{
	Free();
	data = new char[1] {};
}

const char* MyString::c_str() const
{
	return data;
}

void MyString::SaveToFile(std::ofstream& file) const
{
	file.write((const char*)&length, sizeof(length));
	file.write((const char*)data, length + 1);
}

void MyString::ReadFromFile(std::ifstream& file)
{
	Free();
	file.read((char*)&length, sizeof(length));
	data = new char[length + 1];
	file.read((char*)data, length + 1);
}

MyString::MyString()
{
	data = new char[1] {};
}

MyString::MyString(size_t n)
{
	length = GetDigitsCount(n);
	data = new char[length + 1];
	for (int i = (int)(length - 1); i >= 0; i--) //casting to int because of warning
	{
		data[i] = (n % 10) + '0';
		n /= 10;
	}
	data[length] = '\0';
}

MyString::MyString(const char* str)
{
	length = strlen(str);
	data = new char[length + 1];
	strcpy_s(data, length + 1, str);
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs);
	result += rhs;
	return result;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[MAX_BUFFER_SIZE]{};
	is >> buff;
	str.Free();
	str.length = strlen(buff);
	str.data = new char[str.length + 1];
	strcpy_s(str.data, str.length + 1, buff);
	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.data;
	return os;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	if (lhs.length != rhs.length) return false;
	if (strcmp(lhs.data, rhs.data) != 0) return false;
	return true;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.data, rhs.data) > 0;
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.data, rhs.data) < 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.data, rhs.data) >= 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.data, rhs.data) <= 0;
}
