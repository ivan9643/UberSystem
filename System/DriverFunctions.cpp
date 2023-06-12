#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInDriver()
{
	CheckForLoggedDriver();
	cout << "welcome " << loggedDriver->GetUsername() << endl;

	MyString menu = "1 - profile info\n2 - change current location\n3 - check pending orders\n4 - accept order\n5 - decline order\n6 - \n7 - \n0 - logout";

	MyString action;
	while (action != "0") {
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedDriver->PrintData();
		else if (action == "2") DriverChangeCurrentLocation();
		else if (action == "3") DriverCheckPendingOrders();
		else if (action == "4");
		else if (action == "5");
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

void UberSystem::DriverCheckPendingOrders()
{
	CheckForLoggedDriver();
	MyVector<SharedPtr<Order>> pendingOrders = loggedDriver->GetPendingOrders();
}