#include "Client.h"

void Client::AddMoney(double money)
{
	if (money <= 0) throw std::runtime_error("added money must be > 0");
	this->money += money;
}
