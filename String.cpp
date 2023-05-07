#include <cstring>
#include <iostream>
#include "String.h"

void String::CopyFrom(const String& other)
{
	length = other.length;
	data = new char[length + 1];
	strcpy_s(data, length + 1, other.data);
}

void String::CopyFrom(String&& other)
{
	length = other.length;
	data = other.data;
	other.data = nullptr;
}

void String::Free()
{
	delete[] data;
	length = 0;
}

String::String(const String& other)
{
	CopyFrom(other);
}

String::String(String&& other)
{
	CopyFrom(std::move(other));
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}

String& String::operator=(String&& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(std::move(other));
	}
	return *this;
}

char& String::operator[](size_t index)
{
	if (index >= length) throw std::runtime_error("index out of range");
	return data[index];
}

const char String::operator[](size_t index) const
{
	if (index >= length) throw std::runtime_error("index out of range");
	return data[index];
}

String String::operator+=(const String& other)
{
	length += other.length;
	char* newData = new char[length + 1] {};
	strcat_s(newData, length + 1, data);
	strcat_s(newData, length + 1, other.data);
	delete[] data;
	data = newData;
	return *this;
}

String::~String()
{
	Free();
}

bool String::empty() const
{
	return length == 0;
}

void String::clear()
{
	Free();
	data = new char[1] {};
}

const char* String::c_str() const
{
	return data;
}

String::String(const char* str)
{
	length = strlen(str);
	data = new char[length + 1];
	strcpy_s(data, length + 1, str);
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs);
	result += rhs;
	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.length != rhs.length) return false;
	if (strcmp(lhs.data, rhs.data) != 0) return false;
	return true;
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) > 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) < 0;
}

bool operator>=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) >= 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return strcmp(lhs.data, rhs.data) <= 0;
}
