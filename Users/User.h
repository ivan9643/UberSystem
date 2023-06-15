#pragma once
#include <fstream>
#include "../Utilities/MyString.h"
#include "../Utilities/MyVector.hpp"
#include "../SmartPointers/SharedPtr.hpp"

enum class Property {
	username,
	password,
};

class Order;

const size_t MIN_LENGTH = 3;
const size_t MAX_LENGTH = 25; 
//used for username, password, first and last name

class User {
protected:
	MyString username;
	MyString firstName;
	MyString lastName;
	size_t passHash = 0;
	double money = 0;
	size_t id = GetNextId();
	MyVector<SharedPtr<Order>> pendingOrders;
	MyVector<SharedPtr<Order>> completedOrders;

	static size_t nextId;
	static size_t GetNextId();

	void SetPassHash(const MyString& password);

	bool IsUsernameOrPasswordValid(const MyString& username, Property property) const;
	bool IsNameValid(const MyString& name) const;

public:
	User() = default;
	User(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money);

	size_t GetUserId() const;
	const MyString& GetUsername() const;
	const MyString& GetFirstName() const;
	const MyString& GetLastName() const;
	size_t GetPassHash() const;
	double GetMoney() const;

	void SetUsername(const MyString& username);
	void SetFirstName(const MyString& firstName);
	void SetLastName(const MyString& lastName);
	void SetMoney(double money);

	virtual void PrintData() const;

	const MyVector<SharedPtr<Order>>& GetPendingOrders() const;
	const MyVector<SharedPtr<Order>>& GetCompletedOrders() const;
	SharedPtr<Order>& GetPendingOrder(size_t orderId);
	void AddToPendingOrders(const SharedPtr<Order>& order); //check if it must be const
	void RemoveFromPendingOrders(const SharedPtr<Order>& order);
	void AddToCompletedOrders(const SharedPtr<Order>& order);
};