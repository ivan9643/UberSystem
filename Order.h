#pragma once
#include "Driver.h"

class Order {
	Address current;
	Address destination;
	size_t passengersCount = 0;
	size_t id; // think of a way to generate unique ids
	Driver* driver = nullptr;
	bool IsAccepted = false;
};