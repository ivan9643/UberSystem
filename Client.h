#pragma once
#include <fstream>
#include "User.h"

class Client : public User {


public:
	void AddMoney(double money);
};