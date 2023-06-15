#include "UberSystem.h"
#include "../Helpers/HelperFunctions.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::endl;

int UberSystem::IndexByUsername(const MyString& username, UserType& type) const
{
	for (int i = 0; i < clients.GetCurrentSize(); i++)
	{
		if (clients[i]->GetUsername() == username) {
			type = UserType::client;
			return i;
		}
	}
	for (int i = 0; i < drivers.GetCurrentSize(); i++)
	{
		if (drivers[i]->GetUsername() == username) {
			type = UserType::driver;
			return i;
		}
	}
	return -1;
}

bool UberSystem::UsernameInUse(const MyString& username) const {
	UserType type = UserType::none;
	return IndexByUsername(username, type) != -1;
}

void UberSystem::ReadGeneralUserData(MyString& username, MyString& password, MyString& firstName, MyString& lastName) const
{
	ReadData<MyString>("username: ", username);
	ReadData<MyString>("password: ", password);
	ReadData<MyString>("first name: ", firstName);
	ReadData<MyString>("last name: ", lastName);
}

void UberSystem::ReadAdditionalDriverData(MyString& carNumber, size_t& carPassengersCountCapacity, MyString& phoneNumber, MyString& addressName, int& x, int& y) const
{
	ReadData<MyString>("car number: ", carNumber);
	ReadData<size_t>("car passengers count capacity: ", carPassengersCountCapacity);
	ReadData<MyString>("phone number: ", phoneNumber);
	ReadAddressData("current location: ", addressName, x, y);
}

void UberSystem::ReadAddressData(const MyString& prompt, MyString& addressName, int& x, int& y) const
{
	cout << prompt << endl;
	ReadMyStringWithGetLine("   address name: ", addressName);
	ReadData<int>("   x coordinate: ", x);
	ReadData<int>("   y coordinate: ", y);
}

void UberSystem::ReadAddressDataWithDetails(const MyString& prompt, MyString& addressName, int& x, int& y, MyString& details) const
{
	ReadAddressData(prompt, addressName, x, y);
	ReadMyStringWithGetLine("   details (optional): ", details);
}

void UberSystem::AddUser(UserType type, const MyString& username, const MyString& password, const MyString& firstName,
	const MyString& lastName, const MyString& carNumber, size_t carPassengersCountCapacity, const MyString& phoneNumber, const MyString& addressName, int x, int y)
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
			clients.PushBack(new Client(username, password, firstName, lastName, 0));
			break;
		case UserType::driver:
			drivers.PushBack(new Driver(username, password, firstName, lastName, 0,
				carNumber, carPassengersCountCapacity, phoneNumber, Address(addressName, { x,y })));
			break;
		default:
			MyString errorMessage = "invalid user type";
			throw std::runtime_error(errorMessage.c_str());
			break;
		}
		cout << "registration successful" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}
