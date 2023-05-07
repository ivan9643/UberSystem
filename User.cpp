#include "User.h"

User::User(const String& username, const String& password, const String& firstName, const String& lastName, double money)
{
	SetUsername(username);
	//SetPassword(password); 
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
	if (IsUsernameValid(username)) this->username = username;
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
