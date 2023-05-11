#include "Order.h"

void Order::SaveToFile(std::ofstream& file) const
{
	currentLocation.SaveToFile(file);
	destination.SaveToFile(file);
	file.write((const char*)&passengersCount, sizeof(passengersCount));
	file.write((const char*)&id, sizeof(id));
	file.write((const char*)&isAccepted, sizeof(isAccepted));
	if (isAccepted) driver->SaveToFile(file);
}
