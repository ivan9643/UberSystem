#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInDriver()
{
	cout << "welcome " << loggedDriver->GetUsername() << endl;

	MyString menu = "1 - profile info\n2 - change address\n3 - \n4 - \n5 - \n6 - \n7 - \n0 - logout";

	MyString action;
	while (action != "0") {
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedDriver->PrintData();
		else if (action == "2") DriverChangeAddress();
		else if (action == "0") Logout();
		else cout << action + " is not a valid action" << endl;
	}
}

void UberSystem::DriverChangeAddress()
{
	MyString addressName;
	int x, y;
	ReadAddressData(addressName, x, y);
	loggedDriver->SetCurrentLocation(Address(addressName, { x, y }));
}