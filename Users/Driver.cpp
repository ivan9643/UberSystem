#include "Driver.h"
#include "../Entities/Order.h"
#include "../Helpers/HelperFunctions.h"

using std::cout;
using std::cin;
using std::endl;

bool Driver::IsCarNumberValid(const MyString& carNumber) const
{
	MyString errorMessage = "car number length must be in [" + MyString(MIN_CAR_NUMBER_LENGTH) + ", " +
		MyString(MAX_CAR_NUMBER_LENGTH) + "]\ncar number must contain only letters and digits";
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

bool Driver::IsPhoneNumberValid(const MyString& phoneNumber) const
{
	MyString errorMessage = "phone number must contain " + MyString(PHONE_NUMBER_LENGTH) + " digits";
	if (phoneNumber.GetLength() != PHONE_NUMBER_LENGTH) throw std::runtime_error(errorMessage.c_str());
	for (size_t i = 0; i < phoneNumber.GetLength(); i++)
	{
		if (!IsDigit(phoneNumber[i])) 
			throw std::runtime_error(errorMessage.c_str());
	}
	return true;
}

const MyString& Driver::GetCarNumber() const
{
	return carNumber;
}

const MyString& Driver::GetPhoneNumber() const
{
	return phoneNumber;
}

const Address& Driver::GetCurrentLocation() const
{
	return currentLocation;
}

size_t Driver::GetCarPassengersCountCapacity() const
{
	return carPassengersCountCapacity;
}

double Driver::GetRatingValue() const
{
	return rating.value;
}

size_t Driver::GetRatingVotesCount() const
{
	return rating.votesCount;
}

void Driver::PrintData() const
{
	User::PrintData();
	cout << "car number: " << carNumber << endl;
	cout << "car passengers count capacity: " << carPassengersCountCapacity << endl;
	cout << "phone number: " << phoneNumber<< endl;
	cout << "current location:" << endl;
	currentLocation.PrintDataWithoutDetails();
	cout << "rating: " << endl;
	cout << "   value: " << rating.value << endl;
	cout << "   votes count: " << rating.votesCount << endl;
}

void Driver::Rate(double value)
{
	if (value < 1 || value > 5) throw std::runtime_error("rating must be in [1, 5]");
	rating.AddVote(value);
}

void Driver::ReceivePayment(double amount)
{
	if (amount < 0) throw std::runtime_error("amount must be > 0");
	money += amount;
}

void Driver::SetCarNumber(const MyString& carNumber)
{
	if (IsCarNumberValid(carNumber)) this->carNumber = carNumber;
}

void Driver::SetPhoneNumber(const MyString& phoneNumber)
{
	if (IsPhoneNumberValid(phoneNumber)) this->phoneNumber = phoneNumber;
}

void Driver::SetCurrentLocation(const Address& currentLocation)
{
	this->currentLocation = currentLocation;
}

void Driver::SetCarPassengersCountCapacity(size_t carPassengersCountCapacity)
{
	this->carPassengersCountCapacity = carPassengersCountCapacity;
}

Driver::Driver(const MyString& username, const MyString& password, const MyString& firstName,
	const MyString& lastName, double money, const MyString& carNumber, size_t carPassengersCountCapacity, const MyString& phoneNumber,
	const Address& currentLocation)
	:User(username, password, firstName, lastName, money), carPassengersCountCapacity(carPassengersCountCapacity)
{
	SetCarNumber(carNumber);
	SetPhoneNumber(phoneNumber);
	SetCurrentLocation(currentLocation);
}

void Rating::AddVote(double value)
{
	if (votesCount == 0) this->value = value;
	else this->value = (votesCount * this->value + value) / (votesCount + 1);
	votesCount++;
}
