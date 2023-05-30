#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInClient()
{
	WelcomeUser(loggedClient->GetUsername());

	MyString menu = "1 - profile info\n2 - add money\n3 - \n4 - \n5 - \n6 - \n7 - \n0 - logout";

	while (true) {
		MyString action;
		cout << menu << endl;
		cin >> action;

		if (action == "1") loggedClient->PrintData();
		else if (action == "2") ClientAddMoney();
		else if (action == "0") return;
		else cout << action + " is not a valid action" << endl;
	}
}

void UberSystem::ClientAddMoney()
{
	double money;
	ReadData<double>("enter amount:", money);
	try
	{
		loggedClient->AddMoney(money);
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl << endl;
	}
}