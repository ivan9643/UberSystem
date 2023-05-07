#include <fstream>
#include "Driver.h"
#include "HelperFunctions.h"

bool Driver::IsCarNumberValid(const String& carNumber)
{
	String errorMessage = "car number length must be in [" + String(MIN_CAR_NUMBER_LENGTH) + ", " +
		String(MAX_CAR_NUMBER_LENGTH) + "]\ncar number must contain only letters and digits";
	if (carNumber.GetLength() < MIN_CAR_NUMBER_LENGTH) throw std::runtime_error(errorMessage.c_str());
	if (carNumber.GetLength() > MAX_CAR_NUMBER_LENGTH) throw std::runtime_error(errorMessage.c_str());
	for (size_t i = 0; i < carNumber.GetLength(); i++)
	{
		char cur = carNumber[i];
		if (!IsLetter(cur) && !IsDigit(cur))
			throw std::runtime_error(errorMessage.c_str());
	}
	return true;
}

bool Driver::IsPhoneNumberValid(const String& phoneNumber)
{
	String errorMessage = "phone number must contain " + String(PHONE_NUMBER_LENGTH) + " digits";
	if (phoneNumber.GetLength() != PHONE_NUMBER_LENGTH) throw std::runtime_error(errorMessage.c_str());
	for (size_t i = 0; i < phoneNumber.GetLength(); i++)
	{
		if (!IsDigit(phoneNumber[i])) 
			throw std::runtime_error(errorMessage.c_str());
	}
	return true;
}

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

void Driver::ReadFromFile(std::ifstream& file)
{
}

void Driver::SetCarNumber(const String& carNumber)
{
	if (IsCarNumberValid(carNumber)) this->carNumber = carNumber;
}

void Driver::SetPhoneNumber(const String& phoneNumber)
{
	if (IsPhoneNumberValid(phoneNumber)) this->phoneNumber = phoneNumber;
}

Driver::Driver(const String& username, const String& password, const String& firstName,
	const String& lastName, const String& carNumber, const String& phoneNumber, double money)
	:User(username, password, firstName, lastName, money)
{
	SetCarNumber(carNumber);
	SetPhoneNumber(phoneNumber);
}
