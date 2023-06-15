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

	MyString menu = "1 - profile info\n2 - add money\n3 - make order\n4 - check orders"
		"\n5 - cancel order\n6 - pay order\n7 - rate driver\n0 - logout";

	MyString action;
	while (action != "0") {
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedClient->PrintData();
		else if (action == "2") ClientAddMoney();
		else if (action == "3") ClientMakeOrder();
		else if (action == "4") ClientCheckOrders();
		else if (action == "5") ClientCancelOrder();
		else if (action == "6") ClientPayOrder();
		else if (action == "7") ClientRateDriver();
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
		cout << "money added successfully" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::ClientMakeOrder()
{
	CheckForLoggedClient();

	MyString currentLocationName, currentLocationDetails, destinationName, destinationDetails;
	int x1, y1, x2, y2;
	size_t passengersCount;

	ReadAddressDataWithDetails("current location:", currentLocationName, x1, y1, currentLocationDetails);
	ReadAddressDataWithDetails("destination:", destinationName, x2, y2, destinationDetails);
	ReadData<size_t>("passengers count: ", passengersCount);

	try
	{
		Address currentLocation(currentLocationName, { x1, y1 }, currentLocationDetails);
		Address destination(destinationName, { x2, y2 }, destinationDetails);
		MakeOrder(currentLocation, destination, passengersCount);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

}

void UberSystem::MakeOrder(const Address& clientCurrentLocation, const Address& destination, size_t passengersCount)
{
	CheckForLoggedClient();
	SharedPtr<Order> order = new Order(clientCurrentLocation, destination, passengersCount, loggedClient);
	try
	{
		SetNearestDriver(order);

		loggedClient->AddToPendingOrders(order);
		pendingOrders.PushBack(order);

		cout << "order created successfully" << endl;
	}
	catch (const std::runtime_error& e)
	{
		cout << e.what() << endl;

		loggedClient->AddToCancelledOrders(order);
		cancelledOrders.PushBack(order);

		order->Cancel();
		cout << "order cancelled" << endl;
	}
}

void UberSystem::SetNearestDriver(SharedPtr<Order>& order)
{
	if (drivers.GetCurrentSize() == 0)
		throw std::logic_error("no registered drivers");

	size_t minInd = -1;
	double minDist;
	Point clientCoordinates = order->GetClientCurrentLocation().GetCoordinates();
	for (size_t i = 0; i < drivers.GetCurrentSize(); i++)
	{
		if (order->GetDeclinedBy().Contains(drivers[i])) continue;
		if (drivers[i]->GetCarPassengersCountCapacity() < order->GetPassengersCount()) continue;
		if (minInd == -1) {
			minDist = GetDistance(drivers[i]->GetCurrentLocation().GetCoordinates(), clientCoordinates);
			minInd = i;
		}
		double dist = GetDistance(drivers[i]->GetCurrentLocation().GetCoordinates(), clientCoordinates);
		if (dist < minDist)
		{
			minInd = i;
			minDist = dist;
		}
	}

	if (minInd == -1)
		throw std::logic_error("there are currently no drivers available to take the order");

	order->SetDriver(drivers[minInd]);
	drivers[minInd]->AddToPendingOrders(order);
};


void UberSystem::ClientCheckOrders() const
{
	CheckForLoggedClient();

	MyString menu = "1 - pending orders\n2 - completed orders\n3 - cancelled orders\n0 - back";

	MyString action;
	cout << menu << endl;
	cin >> action;

	if (action == "1") ClientPrintOrders(loggedClient->GetPendingOrders(), "pending");
	else if (action == "2") ClientPrintOrders(loggedClient->GetCompletedOrders(), "completed");
	else if (action == "3") ClientPrintOrders(loggedClient->GetCancelledOrders(), "cancelled");
	else if (action == "0") return;
	else cout << action + " is not a valid action" << endl;
}

void UberSystem::ClientPrintOrders(const MyVector<SharedPtr<Order>>& orders, const MyString ordersType) const
{
	if (orders.GetCurrentSize() == 0)
		cout << "there are no " << ordersType << " orders" << endl;
	for (size_t i = 0; i < orders.GetCurrentSize(); i++)
	{
		orders[i]->PrintDataClientView();
		cout << endl;
	}
}

void UberSystem::ClientCancelOrder()
{
	CheckForLoggedClient();

	size_t orderId;
	ReadData<size_t>("order id: ", orderId);

	try
	{
		SharedPtr<Order> order = loggedClient->GetPendingOrder(orderId);
		if (order->GetStatus() == waitingPayment)
			throw std::runtime_error("can't cancel finished order waiting payment");

		loggedClient->RemoveFromPendingOrders(order);
		order->GetDriver()->RemoveFromPendingOrders(order);
		pendingOrders.Remove(order);

		loggedClient->AddToCancelledOrders(order);
		cancelledOrders.PushBack(order);

		order->Cancel();
		cout << "order cancelled" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::ClientPayOrder()
{
	CheckForLoggedClient();

	size_t orderId;
	ReadData<size_t>("order id: ", orderId);

	try
	{
		SharedPtr<Order> order = loggedClient->GetPendingOrder(orderId);
		if (order->GetStatus() != waitingPayment) throw std::runtime_error("order is still waiting to be finished");

		double price = order->GetPrice();
		SharedPtr<Driver> driver = order->GetDriver();

		loggedClient->Pay(price);
		loggedClient->RemoveFromPendingOrders(order);
		loggedClient->AddToCompletedOrders(order);

		driver->ReceivePayment(price);
		driver->RemoveFromPendingOrders(order);
		driver->AddToCompletedOrders(order);

		pendingOrders.Remove(order);
		completedOrders.PushBack(order);

		order->Complete();

		cout << "order payed successfully" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::ClientRateDriver()
{
	CheckForLoggedClient();

	MyString driverUsername;
	double ratingValue;

	ReadData<MyString>("driver username: ", driverUsername);
	ReadData<double>("rating value (from 1 to 5): ", ratingValue);

	MyVector<SharedPtr<Order>> completedOrders = loggedClient->GetCompletedOrders();
	try
	{
		if (completedOrders.GetCurrentSize() == 0)
			throw std::runtime_error("there are no drivers that have completed an order from you");
		for (size_t i = 0; i < completedOrders.GetCurrentSize(); i++)
		{
			if (completedOrders[i]->GetDriver()->GetUsername() == driverUsername) {
				completedOrders[i]->GetDriver()->Rate(ratingValue);
				cout << "successfully rated driver \"" << driverUsername << "\"";
				return;
			}
		}
		MyString errorMessage = "driver with username \"" + driverUsername + "\" has not completed an order from you";
		throw std::runtime_error(errorMessage.c_str());
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}