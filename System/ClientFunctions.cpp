#include "UberSystem.h"
#include "../Helpers/TemplateFunctions.hpp"

using std::cout;
using std::cin;
using std::endl;

void UberSystem::LoggedInClient()
{
	cout << "welcome " << loggedClient->GetUsername() << endl;

	MyString menu = "1 - profile info\n2 - add money\n3 - \n4 - \n5 - \n6 - \n7 - \n0 - logout";

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

void UberSystem::ClientOrder() 
{

}