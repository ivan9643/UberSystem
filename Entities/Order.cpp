#include "Order.h"
#include "../Users/Driver.h"
#include "../Users/Client.h"

using std::cout;
using std::cin;
using std::endl;

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

double Order::GetPrice() const {
	return price;
}

const MyVector<SharedPtr<Driver>>& Order::GetDeclinedBy() const
{
	return declinedBy;
}

SharedPtr<Client>& Order::GetClient()
{
	return client;
}

SharedPtr<Driver>& Order::GetDriver()
{
	return driver;
}

OrderStatus Order::GetStatus() const
{
	return status;
}

void Order::SetDriver(const SharedPtr<Driver>& driver)
{
	this->driver = driver;
}

void Order::PrintStatus() const
{
	cout << "status: ";
	switch (status)
	{
	case waitingToBeAccepted:
		cout << "waiting to be accepted";
		break;
	case accepted:
		cout << "accepted";
		break;
	case cancelled:
		cout << "cancelled";
		break;
	case waitingPayment:
		cout << "waiting payment";
		break;
	case completed:
		cout << "completed";
		break;
	}
	cout << endl;
}

void Order::PrintDataDriverView() const
{
	cout << "order id: " << id << endl;
	cout << "client location: " << endl;
	clientCurrentLocation.PrintData();
	cout << "destination: " << endl;
	destination.PrintData();
	cout << "passengers count: " << passengersCount << endl;
	PrintStatus();
}

void Order::PrintDataClientView() const {
	cout << "order id: " << id << endl;
	PrintStatus();
	if (status == accepted || status == waitingPayment)
	{
		cout << "driver:" << endl;
		cout << "   username: " << driver->GetUsername() << endl;
		cout << "   first name: " << driver->GetFirstName() << endl;
		cout << "   last name: " << driver->GetLastName() << endl;
		cout << "   car number: " << driver->GetCarNumber() << endl;
		cout << "   phone number: " << driver->GetPhoneNumber() << endl;
		cout << "   rating: " << endl;
		cout << "      value: " << driver->GetRatingValue() << endl;
		cout << "      votes count: " << driver->GetRatingVotesCount() << endl;
		cout << "minutes: " << minutes << endl;
		if (status == waitingPayment)
			cout << "order price: " << price << endl;
	}
}

void Order::Accept(size_t minutes)
{
	status = accepted;
	this->minutes = minutes;
}

void Order::SaveToFile(std::ofstream& file) const
{
	clientCurrentLocation.SaveToFile(file);
	destination.SaveToFile(file);
	file.write((const char*)&passengersCount, sizeof(passengersCount));
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&status, sizeof(status));
	client->SaveToFile(file);
	driver->SaveToFile(file);
}

void Order::ReadFromFile(std::ifstream& file)
{
	clientCurrentLocation.ReadFromFile(file);
	destination.ReadFromFile(file);
	file.read((char*)&passengersCount, sizeof(passengersCount));
	file.read((char*)&id, sizeof(id));
	file.read((char*)&status, sizeof(status));
	client->ReadFromFile(file);
	driver->ReadFromFile(file);
}

void Order::WaitingPayment(double price)
{
	status = waitingPayment;
	if (price < 0) throw std::runtime_error("price must be > 0");
	this->price = price;
}

void Order::Cancel()
{
	status = cancelled;
	declinedBy.Clear();
}

void Order::Complete()
{
	status = completed;
}

void Order::Decline(const SharedPtr<Driver>& driver) 
{
	declinedBy.PushBack(driver);
}

void Order::PrintData() const
{
	cout << "order id: " << id << endl;
	cout << "client:" << endl;
	cout << "   username: " << client->GetUsername() << endl;
	cout << "   first name: " << client->GetFirstName() << endl;
	cout << "   last name: " << driver->GetLastName() << endl;
	cout << "   location: " << endl;
	clientCurrentLocation.PrintData();
	cout << "destination: " << endl;
	destination.PrintData();
	cout << "passengers count: " << passengersCount << endl;
	PrintStatus();
	if (status == accepted || status == waitingPayment)
	{
		cout << "driver:" << endl;
		cout << "   username: " << driver->GetUsername() << endl;
		cout << "   first name: " << driver->GetFirstName() << endl;
		cout << "   last name: " << driver->GetLastName() << endl;
		cout << "   car number: " << driver->GetCarNumber() << endl;
		cout << "   phone number: " << driver->GetPhoneNumber() << endl;
		cout << "   rating: " << endl;
		cout << "      value: " << driver->GetRatingValue() << endl;
		cout << "      votes count: " << driver->GetRatingVotesCount() << endl;
		cout << "minutes: " << minutes << endl;
		if (status == waitingPayment)
			cout << "order price: " << price << endl;
	}
}