#pragma once
#include <fstream>
#include "../Utilities/MyVector.hpp"
#include "../SmartPointers/SharedPtr.hpp"
#include "User.h"

class Client : public User {
	MyVector<SharedPtr<Order>> cancelledOrders;
public:
	//Client() = default;
	Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money);
	
	const MyVector<SharedPtr<Order>>& GetCancelledOrders() const;

	void Pay(double amount);
	void AddMoney(double money);
	
	void AddToCancelledOrders(const SharedPtr<Order>& order); //check if it must be const
	void RemoveFromCancelledOrders(const SharedPtr<Order>& order);

};