#include "Client.h"
#include "../Entities/Order.h"

Client::Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money)
	:User(username, password, firstName, lastName, money) {}

const MyVector<SharedPtr<Order>>& Client::GetCancelledOrders() const
{
	return cancelledOrders;
}

void Client::Pay(double amount)
{
	if (amount < 0) throw std::runtime_error("amount must be > 0");
	if (amount > money) throw std::runtime_error("not enough money");
	money -= amount;
}

void Client::AddMoney(double money)
{
	if (money <= 0) throw std::runtime_error("added money must be > 0");
	this->money += money;
}

void Client::AddToCancelledOrders(const SharedPtr<Order>& order)
{
	cancelledOrders.PushBack(order);
}

void Client::RemoveFromCancelledOrders(const SharedPtr<Order>& order)
{
	cancelledOrders.Remove(order);
}

//void Client::SaveToFile(std::ofstream& file) const
//{
//
//}
//
//void Client::ReadFromFile(std::ifstream& file)
//{
//}
