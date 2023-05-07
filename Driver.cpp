#include <fstream>
#include "Driver.h"

const String& Driver::GetCarNumber() const
{
	return carNumber;
}

const String& Driver::GetPhoneNumber() const
{
	return phoneNumber;
}

void Driver::SaveToFile(std::ofstream& file) {

}
