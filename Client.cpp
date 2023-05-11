#include "Client.h"

Client::Client(const String& username, const String& password, const String& firstName, const String& lastName, double money)
	:User(username, password, firstName, lastName, money) {}

void Client::AddMoney(double money)
{
	if (money <= 0) throw std::runtime_error("added money must be > 0");
	this->money += money;
}

//void Client::SaveToFile(std::ofstream& file) const
//{
//
//}
//
//void Client::ReadFromFile(std::ifstream& file)
//{
//}
