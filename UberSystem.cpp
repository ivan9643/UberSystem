#include <fstream>
#include "UberSystem.h"
#include "HelperFunctions.h"

using std::cout;
using std::cin;
using std::endl;


int UberSystem::IndexByUsername(const String& username, UserType& type) const
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

void UberSystem::CheckIfUsernameInUse(const String& username) const {
	UserType type = UserType::none;
	if (IndexByUsername(username, type) != -1) {
		String errorMessage = "username \"" + username + "\" already in use";
		throw std::runtime_error(errorMessage.c_str());
	}
}

UberSystem::UberSystem()
{
	ReadDataFromFile();
}

void UberSystem::NotLoggedIn() {
	String registration = "Registration:\nfor clients:\nregister client <username> <password> <first_name> <last_name>\n"
		"for drivers:\nregister driver <username> <password> <first_name> <last_name>\n<car_number> <phone_number> <x_coordinate> <y_coordinate>";
	String login = "Login:\nlogin <username> <password>";
	cout << registration << endl;
	cout << login << endl << endl;
	while (true) {
		String action, username, password;
		cin >> action;
		if (action == "register")
		{
			String type, firstName, lastName;
			cin >> type >> username >> password >> firstName >> lastName;
			try
			{
				if (type == "client") {
					CheckIfUsernameInUse(username);
					clients.PushBack(Client(username, password, firstName, lastName, 0));
				}
				else if (type == "driver") {
					String carNumber, phoneNumber;
					int x, y; //secure if user enters letters
					cin >> carNumber >> phoneNumber >> x >> y;
					CheckIfUsernameInUse(username);
					drivers.PushBack(Driver(username, password, firstName, lastName, 0, carNumber, phoneNumber, Address({ x,y })));
				}
				else cout << type + " is not a valid type" << endl;
			}
			catch (const std::exception& e) {
				cout << e.what() << endl << endl;
			}
		}
		else if (action == "login")
		{
			cin >> username >> password;
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
				if (clients[index].GetPassHash() == passwordHash)
				{
					//log in 
				}
			}
			else if (type == UserType::driver) 
			{
				if (drivers[index].GetPassHash() == passwordHash)
				{
					//log in 
				}
			}
		}
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
