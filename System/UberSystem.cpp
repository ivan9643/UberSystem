#include <fstream>
#include "UberSystem.h"
#include "../Helpers/HelperFunctions.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

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

void UberSystem::AddUser(UserType type, const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, const MyString& carNumber, const MyString& phoneNumber, const MyString& addressName, int x, int y)
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

UberSystem::UberSystem()
{
	ReadDataFromFile();
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
