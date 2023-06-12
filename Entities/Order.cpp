#include "Order.h"
#include "../Users/Driver.h"


size_t Order::nextId = 1;

size_t Order::GetNextId()
{
	return nextId++;
}

Order::Order(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount, const SharedPtr<Client>& client)
{
	this->clientCurrentLocation = clientCurrentLocation;
	this->destination = destination;
	this->passengersCount = passengersCount;
	this->client = client;
}

const Address& Order::GetClientCurrentLocation() const
{
	return clientCurrentLocation;
}

const Address& Order::GetDestination() const
{
	return destination;
}

size_t Order::GetPassengersCount() const
{
	return passengersCount;
}

size_t Order::GetId() const
{
	return id;
}

const MyVector<SharedPtr<Driver>> Order::GetDeclinedBy() const
{
	return declinedBy;
}

void Order::SetDriver(const SharedPtr<Driver>& driver)
{
	this->driver = driver;
}

void Order::SaveToFile(std::ofstream& file) const
{
	clientCurrentLocation.SaveToFile(file);
	destination.SaveToFile(file);
	file.write((const char*)&passengersCount, sizeof(passengersCount));
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&status, sizeof(status));
	client->SaveToFile(file);
	if (status == accepted || status == finished) driver->SaveToFile(file);
}

void Order::ReadFromFile(std::ifstream& file)
{
	clientCurrentLocation.ReadFromFile(file);
	destination.ReadFromFile(file);
	file.read((char*)&passengersCount, sizeof(passengersCount));
	file.read((char*)&id, sizeof(id));
	file.read((char*)&status, sizeof(status));
	client->ReadFromFile(file);
	if (status == accepted || status == finished) driver->ReadFromFile(file);
}
