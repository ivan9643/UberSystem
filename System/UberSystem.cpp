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
