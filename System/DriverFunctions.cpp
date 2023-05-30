#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInDriver()
{
	WelcomeUser(loggedDriver->GetUsername());

	MyString menu = "1 - profile info\n2 - \n3 - \n4 - \n5 - \n6 - \n7 - \n0 - logout";

	while (true) {
		MyString action;
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedDriver->PrintData();
		else if (action == "2")
		{
		}
		else if (action == "0") return;
		else cout << action + " is not a valid action" << endl;
	}
}