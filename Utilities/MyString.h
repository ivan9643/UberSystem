#pragma once
#include <fstream>

const size_t MAX_BUFFER_SIZE = 1024;
//used for operator>>

class MyString {
	char* data = nullptr;
	size_t length = 0;
	void CopyFrom(const MyString& other);
	void MoveFrom(MyString&& other);
	void Free();
public:
	MyString();
	MyString(size_t n);
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;

	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	MyString operator+=(const MyString& other);

	char& operator[](size_t index);
	const char operator[](size_t index) const;
	
	size_t GetLength() const;
	bool Empty() const;
	void Clear();

	const char* c_str() const;

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);

	~MyString();

	friend std::istream& operator>>(std::istream& is, MyString& str);
	friend std::istream& GetLine(std::istream& is, MyString& str);
	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend bool operator==(const MyString& lhs, const MyString& rhs);
	friend bool operator!=(const MyString& lhs, const MyString& rhs);
	friend bool operator>(const MyString& lhs, const MyString& rhs);
	friend bool operator<(const MyString& lhs, const MyString& rhs);
	friend bool operator>=(const MyString& lhs, const MyString& rhs);
	friend bool operator<=(const MyString& lhs, const MyString& rhs);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);

};

std::istream& operator>>(std::istream& is, MyString& str);
std::ostream& operator<<(std::ostream& os, const MyString& str);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);

MyString operator+(const MyString& lhs, const MyString& rhs);
