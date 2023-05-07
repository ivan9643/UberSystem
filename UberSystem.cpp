#include <fstream>
#include "UberSystem.h"

void UberSystem::Free()
{
	if (clients != nullptr)	delete[] clients;
	if (drivers != nullptr)	delete[] drivers;
}

UberSystem::UberSystem()
{
	ReadDataFromFile();
}

void UberSystem::SaveDataInFile()
{
	std::ofstream file(DATA_FILE_NAME, std::ios::out | std::ios::binary);
	file.write((const char*)clientsCount, sizeof(clientsCount));
	//for (size_t i = 0; i < clientsCount; i++) clients[i].SaveToFile(file);
	file.write((const char*)driversCount, sizeof(driversCount));
	//for (size_t i = 0; i < driversCount; i++) drivers[i].SaveToFile(file);
	file.write((const char*)ordersCount, sizeof(ordersCount));
	//for (size_t i = 0; i < ordersCount; i++) orders[i].SaveToFile(file);
}

void UberSystem::ReadDataFromFile()
{
}

UberSystem::~UberSystem()
{
	Free();
}
