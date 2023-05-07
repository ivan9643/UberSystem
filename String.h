#pragma once

class String {
	char* data;
	size_t length;
	void CopyFrom(const String& other);
	void CopyFrom(String&& other);
	void Free();
public:
	String(const char* str);
	String(const String& other);
	String(String&& other);

	String& operator=(const String& other);
	String& operator=(String&& other);
	String operator+=(const String& other);

	char& operator[](size_t index);
	const char operator[](size_t index) const;

	bool empty() const;
	void clear();

	const char* c_str() const;

	~String();

	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);

	friend String operator+(const String& lhs, const String& rhs);

};

bool operator==(const String& lhs, const String& rhs);
bool operator!=(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);
bool operator>=(const String& lhs, const String& rhs);
bool operator<=(const String& lhs, const String& rhs);

String operator+(const String& lhs, const String& rhs);
