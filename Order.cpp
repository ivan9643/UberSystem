#include "Order.h"
#include "Driver.h"


size_t Order::nextId = 1;

size_t Order::GetNextId()
{
	return nextId++;
}

void Order::SaveToFile(std::ofstream& file) const
{
	currentLocation.SaveToFile(file);
	destination.SaveToFile(file);
	file.write((const char*)&passengersCount, sizeof(passengersCount));
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&isAccepted, sizeof(isAccepted));
	client->SaveToFile(file);
	if (isAccepted) driver->SaveToFile(file);
}

void Order::ReadFromFile(std::ifstream& file)
{
	currentLocation.ReadFromFile(file);
	destination.ReadFromFile(file);
	file.read((char*)&passengersCount, sizeof(passengersCount));
	file.read((char*)&id, sizeof(id));
	file.read((char*)&isAccepted, sizeof(isAccepted));
	client->ReadFromFile(file);
	if (isAccepted) driver->ReadFromFile(file);
}
