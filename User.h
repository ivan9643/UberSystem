#pragma once
#include <fstream>
#include "String.h"

enum class Property {
	username,
	password,
};

class User {
	String username;
	String firstName;
	String lastName;
	size_t passHash;
	double money;

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

	void SaveToFile(std::ofstream& file);
	void ReadFromFile(std::ifstream& file);
};