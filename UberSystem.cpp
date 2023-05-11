#include <fstream>
#include "UberSystem.h"

UberSystem::UberSystem()
{
	ReadDataFromFile();
}

void UberSystem::SaveDataInFile()
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
