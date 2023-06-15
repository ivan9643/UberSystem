#include <fstream>
#include "UberSystem.h"
#include "../Helpers/HelperFunctions.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

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

void UberSystem::ViewTotalMoney() const 
{
	double total = 0;
	for (size_t i = 0; i < completedOrders.GetCurrentSize(); i++)
	{
		total += completedOrders[i]->GetPrice();
	}
	cout << "total money made: " << total << endl;
}