#include "User.h"
#include "../Helpers/HelperFunctions.h"
#include "../Entities/Order.h"

using std::cout;
using std::cin;
using std::endl;

size_t User::nextId = 1;

size_t User::GetNextId()
{
	return nextId++;
}

void User::SetPassHash(const MyString& password)
{
	if (IsUsernameOrPasswordValid(password, Property::password)) passHash = HashPassword(password.c_str());;
}

bool User::IsUsernameOrPasswordValid(const MyString& username, Property property) const
{
	MyString propertyStr;
	switch (property)
	{
	case Property::username:
		propertyStr = "username";
		break;
	case Property::password:
		propertyStr = "password";
		break;
	}
	MyString errorMessage = propertyStr + " length must be in [" + MyString(MIN_LENGTH) + ", " + MyString(MAX_LENGTH) + "]\n" +
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

bool User::IsNameValid(const MyString& name) const
{
	MyString errorMessage = "name length must be in [" + MyString(MIN_LENGTH) + ", " + MyString(MAX_LENGTH) + "]\n"
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

User::User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money)
{
	SetUsername(username);
	SetPassHash(password);
	SetFirstName(firstName);
	SetLastName(lastName);
	SetMoney(money);
}

size_t User::GetUserId() const
{
	return id;
}

const MyString& User::GetUsername() const
{
	return username;
}

const MyString& User::GetFirstName() const
{
	return firstName;
}

const MyString& User::GetLastName() const
{
	return lastName;
}

size_t User::GetPassHash() const
{
	return passHash;
}

double User::GetMoney() const
{
	return money;
}

void User::SetUsername(const MyString& username)
{
	if (IsUsernameOrPasswordValid(username, Property::username)) this->username = username;
}

void User::SetFirstName(const MyString& firstName)
{
	if (IsNameValid(firstName)) this->firstName = firstName;
}

void User::SetLastName(const MyString& lastName)
{
	if (IsNameValid(lastName)) this->lastName = lastName;
}

void User::SetMoney(double money)
{
	if (money < 0) throw std::runtime_error("money can't be < 0");
	this->money = money;
}

void User::PrintData() const
{
	cout << "user id: " << id << endl;
	cout << "username: " << username << endl;
	cout << "first name: " << firstName << endl;
	cout << "last name: " << lastName << endl;
	cout << "money: " << money << endl;
}


const MyVector<SharedPtr<Order>>& User::GetPendingOrders() const
{
	return pendingOrders;
}

const MyVector<SharedPtr<Order>>& User::GetCompletedOrders() const
{
	return completedOrders;
}

void User::AddToPendingOrders(const SharedPtr<Order>& order)
{
	pendingOrders.PushBack(order);
}

void User::RemoveFromPendingOrders(const SharedPtr<Order>& order)
{
	pendingOrders.Remove(order);
}

void User::AddToCompletedOrders(const SharedPtr<Order>& order)
{
	completedOrders.PushBack(order);
}

SharedPtr<Order>& User::GetPendingOrder(size_t orderId)
{
	for (size_t i = 0; i < pendingOrders.GetCurrentSize(); i++)
	{
		if (pendingOrders[i]->GetId() == orderId)
		{
			return pendingOrders[i];
		}
	}
	MyString errorMessage = "order with id - " + MyString(orderId) + " is not in pending orders";
	throw std::runtime_error(errorMessage.c_str());
}
