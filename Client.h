#pragma once
#include <fstream>
#include "User.h"

class Client : public User {


public:
	Client() = default;
	Client(const String& username, const String& password, const String& firstName, const String& lastName, double money);

	void AddMoney(double money);
	//void SaveToFile(std::ofstream& file) const override;
	//void ReadFromFile(std::ifstream& file) override;

};