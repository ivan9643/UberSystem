#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInDriver()
{
	CheckForLoggedDriver();

	cout << "welcome " << loggedDriver->GetUsername() << endl;

	MyString menu = "1 - profile info\n2 - change current location\n3 - check orders"
		"\n4 - accept order\n5 - decline order\n6 - finish order\n0 - logout";

	MyString action;
	while (action != "0") {
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedDriver->PrintData();
		else if (action == "2") DriverChangeCurrentLocation();
		else if (action == "3") DriverCheckOrders();
		else if (action == "4") DriverAcceptOrder();
		else if (action == "5") DriverDeclineOrder();
		else if (action == "6") DriverFinishOrder();
		else if (action == "0") Logout();
		else cout << action + " is not a valid action" << endl;
	}
}

void UberSystem::DriverChangeCurrentLocation()
{
	CheckForLoggedDriver();

	MyString currentLocationName;
	int x, y;
	try
	{
		ReadAddressData("new current location:", currentLocationName, x, y);
		loggedDriver->SetCurrentLocation(Address(currentLocationName, { x, y }));
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::DriverCheckOrders() const
{
	CheckForLoggedDriver();

	MyString menu = "1 - pending orders\n2 - completed orders\n0 - back";

	MyString action;
	cout << menu << endl;
	cin >> action;

	if (action == "1") DriverPrintOrders(loggedDriver->GetPendingOrders(), "pending");
	else if (action == "2") DriverPrintOrders(loggedDriver->GetCompletedOrders(), "completed");
	else if (action == "0") return;
	else cout << action + " is not a valid action" << endl;
}

void UberSystem::DriverAcceptOrder()
{
	CheckForLoggedDriver();

	size_t orderId;
	size_t minutes;

	ReadData<size_t>("order id: ", orderId);
	ReadData<size_t>("minutes: ", minutes);

	try
	{
		loggedDriver->GetPendingOrder(orderId)->Accept(minutes);
		cout << "order accepted" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::DriverFinishOrder() {
	CheckForLoggedDriver();

	size_t orderId;
	double price;

	ReadData<size_t>("order id: ", orderId);
	ReadData<double>("order price: ", price);

	try
	{
		SharedPtr<Order> order = loggedDriver->GetPendingOrder(orderId);
		order->WaitingPayment(price);
		loggedDriver->SetCurrentLocation(order->GetDestination());
		cout << "order finished" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void UberSystem::DriverDeclineOrder()
{
	CheckForLoggedDriver();

	size_t orderId;

	ReadData<size_t>("order id: ", orderId);

	try
	{
		SharedPtr<Order> order = loggedDriver->GetPendingOrder(orderId);
		if (order->GetStatus() == waitingPayment || order->GetStatus() == accepted)
			throw std::runtime_error("you have already accepted this order");
		loggedDriver->RemoveFromPendingOrders(order);
		order->Decline(loggedDriver);
		cout << "order declined" << endl;
		SetNearestDriver(order);
	}
	catch (const std::logic_error& e)
	{
		cout << e.what() << endl;
		SharedPtr<Order> order = loggedDriver->GetPendingOrder(orderId);
		SharedPtr<Client> client = order->GetClient();

		client->RemoveFromPendingOrders(order);
		client->AddToCancelledOrders(order);

		pendingOrders.Remove(order);
		cancelledOrders.PushBack(order);

		order->Cancel();
		cout << "order cancelled" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}


void UberSystem::DriverPrintOrders(const MyVector<SharedPtr<Order>>& orders, const MyString ordersType) const
{
	if (orders.GetCurrentSize() == 0)
		cout << "there are no " << ordersType << " orders" << endl;
	for (size_t i = 0; i < orders.GetCurrentSize(); i++)
	{
		orders[i]->PrintDataDriverView();
		cout << endl;
	}
}