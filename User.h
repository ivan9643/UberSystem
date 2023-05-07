#pragma once
#include <fstream>
#include "String.h"

class User {
	String username;
	String password; //check if password hashing is required
	String firstName;
	String lastName;
	double money;
	//set password private
	bool IsUsernameValid(const String&) const;
	bool IsNameValid(const String&) const;

public:
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