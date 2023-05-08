#include <iostream>
#include <fstream>
#include "Client.h"
#include "Driver.h"

int main()
{
	String username = "username";
	String firstName = "First";
	String lastName = "Last";
	String password = "password";
	String carNumber = "carNumber";
	String phoneNumber = "0878309849";
	Address curLoc("name", "details", { 1,1 });
	//User u(username, password, firstName, lastName, 0);

	//Client c(username, password, firstName, lastName, 0);
	Driver d(username, password, firstName, lastName, 0, carNumber, phoneNumber, curLoc);
	std::ofstream file("file.txt", std::ios::binary);
	d.SaveToFile(file);
	file.close();
	Driver d2;
	std::ifstream file2("file.txt", std::ios::binary);
	d2.ReadFromFile(file2);
	file2.close();
}
