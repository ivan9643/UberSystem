#pragma once

class String {
	char* data = nullptr;
	size_t length = 0;
	void CopyFrom(const String& other);
	void MoveFrom(String&& other);
	void Free();
public:
	String();
	String(size_t n);
	String(const char* str);
	String(const String& other);
	String(String&& other) noexcept;

	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	String operator+=(const String& other);

	char& operator[](size_t index);
	const char operator[](size_t index) const;
	
	size_t GetLength() const;
	bool empty() const;
	void clear();

	const char* c_str() const;

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);

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
