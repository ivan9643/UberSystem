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
	String errorMessage = propertyStr + " length must be in [" + String(MIN_LENGTH) + ", " + String(MAX_LENGTH) + "]\n" +
		propertyStr + " must contain only letters, digits, dots (.) and underscores (_)";
	if (username.GetLength() < MIN_LENGTH) throw std::runtime_error(errorMessage.c_str());
	if (username.GetLength() > MAX_LENGTH) throw std::runtime_error(errorMessage.c_str());
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
	String errorMessage = "name length must be in [" + String(MIN_LENGTH) + ", " + String(MAX_LENGTH) + "]\n"
		"name must start with an uppercase letter and the rest must be lowercase";
	if (name.GetLength() < MIN_LENGTH) throw std::runtime_error(errorMessage.c_str());
	if (name.GetLength() > MAX_LENGTH) throw std::runtime_error(errorMessage.c_str());
	if (!IsUpper(name[0])) throw std::runtime_error(errorMessage.c_str());
	for (size_t i = 1; i < name.GetLength(); i++)
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
	SetMoney(money);
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

void User::SaveToFile(std::ofstream& file)
{
	username.SaveToFile(file);
	firstName.SaveToFile(file);
	lastName.SaveToFile(file);
	file.write((const char*)&passHash, sizeof(passHash));
	file.write((const char*)&money, sizeof(money));
}

void User::ReadFromFile(std::ifstream& file)
{
	username.ReadFromFile(file);
	firstName.ReadFromFile(file);
	lastName.ReadFromFile(file);
	file.read((char*)&passHash, sizeof(passHash));
	file.read((char*)&money, sizeof(money));
}
