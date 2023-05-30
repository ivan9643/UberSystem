#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::endl;

int UberSystem::IndexByUsername(const MyString& username, UserType& type, bool errorMessage) const
{
	for (size_t i = 0; i < clients.currentSize; i++)
	{
		if (clients[i].GetUsername() == username) {
			type = UserType::client;
			return i;
		}
	}
	for (size_t i = 0; i < drivers.currentSize; i++)
	{
		if (drivers[i].GetUsername() == username) {
			type = UserType::driver;
			return i;
		}
	}
	if (errorMessage) cout << "user with username \"" + username + "\" does ot exist" << endl;
	return -1;
}

bool UberSystem::UsernameInUse(const MyString& username) const {
	UserType type = UserType::none;
	return IndexByUsername(username, type, false) != -1;
}

void UberSystem::ReadGeneralUserData(MyString& username, MyString& password, MyString& firstName, MyString& lastName) const
{
	ReadData<MyString>("enter username:", username);
	ReadData<MyString>("enter password:", password);
	ReadData<MyString>("enter first name:", firstName);
	ReadData<MyString>("enter last name:", lastName);
}

void UberSystem::ReadAdditionalDriverData(MyString& carNumber, MyString& phoneNumber, MyString& addressName, int& x, int& y) const
{
	ReadData<MyString>("enter car number:", carNumber);
	ReadData<MyString>("enter phone number:", phoneNumber);
	ReadMyStringWithGetLine("enter current address name:", addressName);
	ReadData<int>("enter x coordinate:", x);
	ReadData<int>("enter y coordinate:", y);
}

void UberSystem::AddUser(UserType type, const MyString& username, const MyString& password, const MyString& firstName,
	const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber, const MyString& addressName, int x, int y)
{
	try
	{
		if (UsernameInUse(username)) {
			MyString errorMessage = "username \"" + username + "\" already in use";
			throw std::runtime_error(errorMessage.c_str());
		}
		switch (type)
		{
		case UserType::client:
			clients.PushBack(Client(username, password, firstName, lastName, 0));
			break;
		case UserType::driver:
			drivers.PushBack(Driver(username, password, firstName, lastName, 0,
				carNumber, phoneNumber, Address(addressName, { x,y })));
			break;
		default:
			MyString errorMessage = "invalid user type";
			throw std::runtime_error(errorMessage.c_str());
			break;
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl << endl;
	}
}