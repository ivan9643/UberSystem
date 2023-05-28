#include "Client.h"

Client::Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money)
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
