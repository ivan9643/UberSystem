#include <fstream>
#include "UberSystem.h"
#include "../Helpers/HelperFunctions.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

UberSystem::UberSystem()
{
	ReadDataFromFile();
}

void UberSystem::ViewUsers() const
{
	if (clients.GetCurrentSize() == 0)
		cout << "there are no registered clients" << endl;
	else cout << "clients: " << endl;
	for (size_t i = 0; i < clients.GetCurrentSize(); i++)
	{
		clients[i]->PrintData();
		cout << endl;
	}
	if (drivers.GetCurrentSize() == 0)
		cout << "there are no registered drivers" << endl;
	else cout << "drivers: " << endl;
	for (size_t i = 0; i < drivers.GetCurrentSize(); i++)
	{
		drivers[i]->PrintData();
		cout << endl;
	}
}

void UberSystem::ViewOrders() const
{
	MyString menu = "1 - pending orders\n2 - completed orders\n3 - cancelled orders\n0 - back";

	MyString action;
	cout << menu << endl;
	cin >> action;

	if (action == "1") PrintOrders(pendingOrders, "pending");
	else if (action == "2") PrintOrders(completedOrders, "completed");
	else if (action == "3") PrintOrders(cancelledOrders, "cancelled");
	else if (action == "0") return;
	else cout << action + " is not a valid action" << endl;
}

void UberSystem::PrintOrders(const MyVector<SharedPtr<Order>>& orders, const MyString ordersType) const 
{
	if (orders.GetCurrentSize() == 0)
		cout << "there are no " << ordersType << " orders" << endl;
	for (size_t i = 0; i < orders.GetCurrentSize(); i++)
	{
		orders[i]->PrintData();
		cout << endl;
	}
}

void UberSystem::SaveDataInFile() const
{
	std::ofstream file(DATA_FILE_NAME, std::ios::out | std::ios::binary);

	file.write((const char*)&clients.capacity, sizeof(clients.capacity));
	file.write((const char*)&clients.currentSize, sizeof(clients.currentSize));
	for (size_t i = 0; i < clients.currentSize; i++) clients[i]->SaveToFile(file);

	file.write((const char*)&drivers.capacity, sizeof(drivers.capacity));
	file.write((const char*)&drivers.currentSize, sizeof(drivers.currentSize));
	for (size_t i = 0; i < drivers.currentSize; i++) drivers[i]->SaveToFile(file);

	file.write((const char*)&completedOrders.capacity, sizeof(completedOrders.capacity));
	file.write((const char*)&completedOrders.currentSize, sizeof(completedOrders.currentSize));
	for (size_t i = 0; i < completedOrders.currentSize; i++) completedOrders[i]->SaveToFile(file);

	file.write((const char*)&pendingOrders.capacity, sizeof(pendingOrders.capacity));
	file.write((const char*)&pendingOrders.currentSize, sizeof(pendingOrders.currentSize));
	for (size_t i = 0; i < pendingOrders.currentSize; i++) pendingOrders[i]->SaveToFile(file);
}

void UberSystem::ReadDataFromFile()
{
	std::ifstream file(DATA_FILE_NAME, std::ios::in | std::ios::binary);

	file.read((char*)&clients.capacity, sizeof(clients.capacity));
	file.read((char*)&clients.currentSize, sizeof(clients.currentSize));
	for (size_t i = 0; i < clients.currentSize; i++) clients[i]->ReadFromFile(file);

	file.read((char*)&drivers.capacity, sizeof(drivers.capacity));
	file.read((char*)&drivers.currentSize, sizeof(drivers.currentSize));
	for (size_t i = 0; i < drivers.currentSize; i++) drivers[i]->ReadFromFile(file);

	file.read((char*)&completedOrders.capacity, sizeof(completedOrders.capacity));
	file.read((char*)&completedOrders.currentSize, sizeof(completedOrders.currentSize));
	for (size_t i = 0; i < completedOrders.currentSize; i++) completedOrders[i]->ReadFromFile(file);

	file.read((char*)&pendingOrders.capacity, sizeof(pendingOrders.capacity));
	file.read((char*)&pendingOrders.currentSize, sizeof(pendingOrders.currentSize));
	for (size_t i = 0; i < pendingOrders.currentSize; i++) pendingOrders[i]->ReadFromFile(file);
}
