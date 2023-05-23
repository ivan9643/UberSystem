#include <fstream>
#include "UberSystem.h"
#include "HelperFunctions.h"

using std::cout;
using std::cin;
using std::endl;


int UberSystem::IndexByUsername(const MyString& username, UserType& type) const
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
	return -1;
}

void UberSystem::CheckIfUsernameInUse(const MyString& username) const {
	UserType type = UserType::none;
	if (IndexByUsername(username, type) != -1) {
		MyString errorMessage = "username \"" + username + "\" already in use";
		throw std::runtime_error(errorMessage.c_str());
	}
}

void UberSystem::ReadGeneralUserData(MyString& username, MyString& password, MyString& firstName, MyString& lastName) const
{
	ReadData<MyString>("Enter username:", username);
	ReadData<MyString>("Enter password:", password);
	ReadData<MyString>("Enter first name:", firstName);
	ReadData<MyString>("Enter last name:", lastName);
}

void UberSystem::ReadAdditionalDriverData(MyString& carNumber, MyString& phoneNumber, MyString& addressName, int& x, int& y) const
{
	ReadData<MyString>("Enter car number:", carNumber);
	ReadData<MyString>("Enter phone number:", phoneNumber);
	ReadData<MyString>("Enter address name:", addressName);
	ReadData<int>("Enter x coordinate:", x);
	ReadData<int>("Enter y coordinate:", y);
}

void UberSystem::AddUser(UserType type, const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber, const MyString& addressName, int x, int y)
{
	try
	{
		CheckIfUsernameInUse(username);
		switch (type)
		{
		case UserType::client:
			clients.PushBack(Client(username, password, firstName, lastName, 0));
			break;
		case UserType::driver:
			drivers.PushBack(Driver(username, password, firstName, lastName, 0, carNumber, phoneNumber,
				Address(addressName, { x,y })));
			break;
		default:
			break;
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl << endl;
	}
}


void UberSystem::LoggedInClient()
{
}

void UberSystem::LoggedInDriver()
{
}

UberSystem::UberSystem()
{
	ReadDataFromFile();
}

void UberSystem::NotLoggedIn() {
	MyString menu = "1 - register\n2 - login\n0 - exit";
	MyString registerMenu = "1 - client\n2 - driver\n0 - back";

	//MyString registration = "Registration:\nfor clients:\nregister client <username> <password> <first_name> <last_name>\n"
	//	"for drivers:\nregister driver <username> <password> <first_name> <last_name>\n<car_number> <phone_number> <x_coordinate> <y_coordinate>";
	//MyString login = "Login:\nlogin <username> <password>";

	while (true) {
		MyString action, username, password;
		cout << menu << endl;
		cin >> action;

		if (action == "1")
		{
			MyString firstName, lastName;
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
			else if (action == "0") continue;
			else cout << action + " is not a valid action" << endl;
		}
		else if (action == "2")
		{
			ReadData<MyString>("Enter username:", username);
			ReadData<MyString>("Enter password:", password);
			UserType type = UserType::none;
			int index = IndexByUsername(username, type);
			if (index == -1)
			{
				cout << "user with username \"" + username + "\" does ot exist";
				continue;
			}
			size_t passwordHash = HashPassword(password.c_str());
			if (type == UserType::client)
			{
				if (clients[index].GetPassHash() == passwordHash) {
					loggedUser = &clients[index];

				}
				else cout << "incorrect password";
			}
			else if (type == UserType::driver)
			{
				if (drivers[index].GetPassHash() == passwordHash) {
					loggedUser = &drivers[index];

				}
				else cout << "incorrect password";
			}
		}
		else if (action == "0") return;
		else cout << action + " is not a valid action" << endl;
	}
}

void UberSystem::SaveDataInFile() const
{
	std::ofstream file(DATA_FILE_NAME, std::ios::out | std::ios::binary);

	file.write((const char*)&clients.capacity, sizeof(clients.capacity));
	file.write((const char*)&clients.currentSize, sizeof(clients.currentSize));
	for (size_t i = 0; i < clients.currentSize; i++) clients[i].SaveToFile(file);

	file.write((const char*)&drivers.capacity, sizeof(drivers.capacity));
	file.write((const char*)&drivers.currentSize, sizeof(drivers.currentSize));
	for (size_t i = 0; i < drivers.currentSize; i++) drivers[i].SaveToFile(file);

	file.write((const char*)&orders.capacity, sizeof(orders.capacity));
	file.write((const char*)&orders.currentSize, sizeof(orders.currentSize));
	for (size_t i = 0; i < orders.currentSize; i++) orders[i].SaveToFile(file);
}

void UberSystem::ReadDataFromFile()
{
	std::ifstream file(DATA_FILE_NAME, std::ios::in | std::ios::binary);

	file.read((char*)&clients.capacity, sizeof(clients.capacity));
	file.read((char*)&clients.currentSize, sizeof(clients.currentSize));
	for (size_t i = 0; i < clients.currentSize; i++) clients[i].ReadFromFile(file);

	file.read((char*)&drivers.capacity, sizeof(drivers.capacity));
	file.read((char*)&drivers.currentSize, sizeof(drivers.currentSize));
	for (size_t i = 0; i < drivers.currentSize; i++) drivers[i].ReadFromFile(file);

	file.read((char*)&orders.capacity, sizeof(orders.capacity));
	file.read((char*)&orders.currentSize, sizeof(orders.currentSize));
	for (size_t i = 0; i < orders.currentSize; i++) orders[i].ReadFromFile(file);
}
