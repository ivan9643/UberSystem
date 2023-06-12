#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"
#include "../Helpers/HelperFunctions.h"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInClient()
{
	CheckForLoggedClient();
	cout << "welcome " << loggedClient->GetUsername() << endl;

	MyString menu = "1 - profile info\n2 - add money\n3 - make order\n4 - \n5 - \n6 - \n7 - \n0 - logout";

	MyString action;
	while (action != "0") {
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedClient->PrintData();
		else if (action == "2") ClientAddMoney();
		else if (action == "3") ClientOrder();
		else if (action == "0") Logout();
		else cout << action + " is not a valid action" << endl;
	}
}

void UberSystem::ClientAddMoney()
{
	CheckForLoggedClient();
	double money;
	ReadData<double>("enter amount: ", money);
	try
	{
		loggedClient->AddMoney(money);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::ClientOrder() 
{
	CheckForLoggedClient();

	MyString currentLocationName, currentLocationDetails, destinationName, destinationDetails;
	int x1, y1, x2, y2;
	size_t passengersCount;

	ReadAddressDataWithDetails("current location:", currentLocationName, x1, y1, currentLocationDetails);
	ReadAddressDataWithDetails("destination:", destinationName, x2, y2, destinationDetails);
	ReadData<size_t>("passengers count: ", passengersCount);

	Address currentLocation(currentLocationName, {x1, y1}, currentLocationDetails);
	Address destination(destinationName, {x2, y2}, destinationDetails);

	MakeOrder(currentLocation, destination, passengersCount);
}

void UberSystem::MakeOrder(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount) 
{
	CheckForLoggedClient();
	SharedPtr<Order> order = new Order(clientCurrentLocation, destination, passengersCount, loggedClient);
	try
	{
		SetNearestDriver(order);
		cout << "order created successfully";
	}
	catch (const std::runtime_error& e)
	{
		cout << e.what() << endl;
		//cancel order
		cout << "order cancelled" << endl;
	}
}

void UberSystem::SetNearestDriver(SharedPtr<Order>& order) {
	if (drivers.GetCurrentSize() == 0) 
		throw std::runtime_error("no registered drivers");

	size_t minInd = -1;
	double minDist;

	for (size_t i = 0; i < drivers.GetCurrentSize(); i++)
	{
		if (order->GetDeclinedBy().Contains(drivers[i])) continue;
		if (drivers[i]->GetCarPassengersCountCapacity() < order->GetPassengersCount()) continue;
		if (minInd == -1) {
			minDist = GetDistance(drivers[i]->GetCurrentLocation().GetCoordinates(),
				order->GetClientCurrentLocation().GetCoordinates());
			minInd = i;
		}
		double dist = GetDistance(drivers[i]->GetCurrentLocation().GetCoordinates(),
			order->GetClientCurrentLocation().GetCoordinates());
		if (dist < minDist)
		{
			minInd = i;
			minDist = dist;
		}
	}

	if (minInd == -1)
		throw std::runtime_error("all drivers declined this order");
	
	order->SetDriver(drivers[minInd]);
	drivers[minInd]->AddOrder(order);
};
