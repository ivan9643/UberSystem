#pragma once
#include <fstream>
#include "User.h"

class Client : public User {


public:
	Client() = default;
	Client(const MyString& username, const MyString& password, const MyString& firstName, const MyString& lastName, double money);

	void AddMoney(double money);
	//void SaveToFile(std::ofstream& file) const override;
	//void ReadFromFile(std::ifstream& file) override;

};