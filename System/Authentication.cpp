#include "UberSystem.h"
#include "../Helpers/HelperFunctions.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::NotLoggedIn() {
	MyString menu = "1 - register\n2 - login\n0 - exit";
	MyString action;
	
	while (true) {
		cout << menu << endl;
		cin >> action;

		if (action == "1") Register();
		else if (action == "2") Login();
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
		ReadGeneralUserData(username, password, firstName, lastName);
		ReadAdditionalDriverData(carNumber, phoneNumber, addressName, x, y);
		AddUser(UserType::driver, username, password, firstName, lastName, carNumber, phoneNumber, addressName, x, y);
	}
	else if (action == "0") return;
	else cout << action + " is not a valid action" << endl;
}

void UberSystem::Login()
{
	MyString username, password;
	UserType type = UserType::none;
	ReadData<MyString>("enter username:", username);
	int index = IndexByUsername(username, type);
	if (index == -1)
	{
		cout << "user with username \"" + username + "\" does ot exist" << endl;
		return;
	}
	ReadData<MyString>("enter password:", password);
	size_t passwordHash = HashPassword(password.c_str());

	if (type == UserType::client)
	{
		if (clients[index].GetPassHash() == passwordHash) {
			loggedClient = &clients[index];
			loggedUserType = UserType::client;
			LoggedInClient();
			return;
		}
		else cout << "incorrect password";
	}
	else if (type == UserType::driver)
	{
		if (drivers[index].GetPassHash() == passwordHash) {
			loggedDriver = &drivers[index];
			loggedUserType = UserType::driver;
			LoggedInDriver();
			return;
		}
		else cout << "incorrect password";
	}
}

void UberSystem::CheckForLoggedUser() const
{
	MyString errorMessage = "there is no logged user";
	switch (loggedUserType)
	{
	case UserType::client:
		if (loggedClient.isNullPtr())
			throw std::runtime_error(errorMessage.c_str());
		break;
	case UserType::driver:
		if (loggedDriver.isNullPtr())
			throw std::runtime_error(errorMessage.c_str());
		break;
	default:
		throw std::runtime_error(errorMessage.c_str());
		break;
	}
}

void UberSystem::WelcomeUser(const MyString& username) const
{
	cout << "welcome " << username << endl;
}