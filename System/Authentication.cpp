#include "UberSystem.h"
#include "../Helpers/HelperFunctions.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::NotLoggedIn() {
	MyString menu = "1 - register\n2 - login\n3 - view users (testing)\n4 - view orders (testing)\n5 - view total money made\n0 - exit";
	MyString action;

	while (true) {
		cout << menu << endl;
		cin >> action;

		if (action == "1") Register();
		else if (action == "2") Login();
		else if (action == "3") ViewUsers();
		else if (action == "4") ViewOrders();
		else if (action == "5") ViewTotalMoney();
		else if (action == "0") return;
		else cout << action + " is not a valid action" << endl;
	}
}

void UberSystem::Register()
{
	MyString registerMenu = "1 - client\n2 - driver\n0 - back";
	MyString action, username, password, firstName, lastName;
	cout << registerMenu << endl;
	cin >> action;

	if (action == "1")
	{
		ReadGeneralUserData(username, password, firstName, lastName);
		AddUser(UserType::client, username, password, firstName, lastName);
	}
	else if (action == "2")
	{
		MyString carNumber, phoneNumber, addressName;
		int x, y;
		size_t carPassengersCountCapacity;
		ReadGeneralUserData(username, password, firstName, lastName);
		ReadAdditionalDriverData(carNumber, carPassengersCountCapacity, phoneNumber, addressName, x, y);
		AddUser(UserType::driver, username, password, firstName, lastName, carNumber, carPassengersCountCapacity, phoneNumber, addressName, x, y);
	}
	else if (action == "0") return;
	else cout << action + " is not a valid action" << endl;
}

void UberSystem::Login()
{
	MyString username, password;
	UserType type = UserType::none;
	ReadData<MyString>("enter username: ", username);
	int index = IndexByUsername(username, type);
	if (index == -1)
	{
		cout << "user with username \"" + username + "\" does ot exist" << endl;
		return;
	}
	ReadData<MyString>("enter password: ", password);
	size_t passwordHash = HashPassword(password.c_str());

	if (type == UserType::client)
	{
		if (clients[index]->GetPassHash() == passwordHash) {
			loggedClient = clients[index];
			loggedUserType = UserType::client;
			LoggedInClient();
			return;
		}
		else cout << "incorrect password";
	}
	else if (type == UserType::driver)
	{
		if (drivers[index]->GetPassHash() == passwordHash) {
			loggedDriver = drivers[index];
			loggedUserType = UserType::driver;
			LoggedInDriver();
			return;
		}
		else cout << "incorrect password";
	}
}

void UberSystem::Logout() {
	if (loggedUserType == UserType::client) loggedClient = nullptr;
	else if (loggedUserType == UserType::driver) loggedDriver = nullptr; //fix error
	loggedUserType = UserType::none;
}

void UberSystem::CheckForLoggedUser() const
{
	MyString errorMessage = "there is no logged user";
	try
	{
		CheckForLoggedClient();
		CheckForLoggedDriver();
	}
	catch (const std::exception&)
	{
		throw std::runtime_error(errorMessage.c_str());
	}
}

void UberSystem::CheckForLoggedClient() const
{
	MyString errorMessage = "there is no logged client";
	switch (loggedUserType)
	{
	case UserType::client:
		if (loggedClient.IsNullPtr())
			throw std::runtime_error(errorMessage.c_str());
		break;
	default:
		throw std::runtime_error(errorMessage.c_str());
		break;
	}
}

void UberSystem::CheckForLoggedDriver() const
{
	MyString errorMessage = "there is no logged driver";
	switch (loggedUserType)
	{
	case UserType::driver:
		if (loggedDriver.IsNullPtr())
			throw std::runtime_error(errorMessage.c_str());
		break;
	default:
		throw std::runtime_error(errorMessage.c_str());
		break;
	}
}
