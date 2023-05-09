#pragma once
#include <fstream>
#include "String.h"

enum class Property {
	username,
	password,
};

const size_t MIN_LENGTH = 3;
const size_t MAX_LENGTH = 25; 
//used for username, password, first and last name

class User {
//protected:
	String username;
	String firstName;
	String lastName;
	size_t passHash = 0;
	double money = 0;

	void SetPassHash(const String& password);

	bool IsUsernameOrPasswordValid(const String& username, Property property) const; //add bool parameter for error message?
	bool IsNameValid(const String& name) const;

public:
	User() = default;
	User(const String& username, const String& password, const String& firstName, const String& lastName, double money);

	const String& GetUsername() const;
	const String& GetFirstName() const;
	const String& GetLastName() const;
	double GetMoney() const;

	void SetUsername(const String& username); // add bool parameter for error message?
	void SetFirstName(const String& firstName);
	void SetLastName(const String& lastName);
	void SetMoney(double money);

	void SaveToFile(std::ofstream& file) const;
	void ReadFromFile(std::ifstream& file);
};