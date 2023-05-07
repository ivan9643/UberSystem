#include "User.h"
#include "HelperFunctions.h"

void User::SetPassHash(const String& password)
{
	if (IsUsernameOrPasswordValid(password, Property::password)) passHash = Hash(password.c_str());;
}

bool User::IsUsernameOrPasswordValid(const String& username, Property property) const
{
	String propertyStr;
	switch (property)
	{
	case Property::username:
		propertyStr = "username";
		break;
	case Property::password:
		propertyStr = "password";
		break;
	}
	String errorMessage = propertyStr + " length must be in [3, 25]\n" + 
		propertyStr + " must contain only letters, digits, dots (.) and underscores (_)" ;
	if (username.GetLength() < 3) throw std::runtime_error(errorMessage.c_str());
	if (username.GetLength() > 25) throw std::runtime_error(errorMessage.c_str());
	for (size_t i = 0; i < username.GetLength(); i++)
	{
		char cur = username[i];
		if (!IsLetter(cur) && !IsDigit(cur) && cur != '.' && cur != '_')
			throw std::runtime_error(errorMessage.c_str());
	}
	return true;
}

bool User::IsNameValid(const String& name) const
{
	String errorMessage = "name length must be in [3, 25]\nname must start with uppercase letter";
	if (name.GetLength() < 3) throw std::runtime_error(errorMessage.c_str());
	if (name.GetLength() > 25) throw std::runtime_error(errorMessage.c_str());
	if (!IsUpper(name[0])) throw std::runtime_error(errorMessage.c_str());
	for (size_t i = 0; i < name.GetLength(); i++)
	{
		if (!IsLower(name[i])) throw std::runtime_error(errorMessage.c_str());
	}
	return true;
}

User::User(const String& username, const String& password, const String& firstName, const String& lastName, double money)
{
	SetUsername(username);
	SetPassHash(password);
	SetFirstName(firstName);
	SetLastName(lastName);
}

const String& User::GetUsername() const
{
	return username;
}

const String& User::GetFirstName() const
{
	return firstName;
}

const String& User::GetLastName() const
{
	return lastName;
}

double User::GetMoney() const
{
	return money;
}

void User::SetUsername(const String& username)
{
	if (IsUsernameOrPasswordValid(username, Property::username)) this->username = username;
}

void User::SetFirstName(const String& firstName)
{
	if (IsNameValid(firstName)) this->firstName = firstName;
}

void User::SetLastName(const String& lastName)
{
	if (IsNameValid(lastName)) this->lastName = lastName;
}

void User::SetMoney(double money)
{
	if (money >= 0) this->money = money;
}
