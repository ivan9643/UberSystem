#include <iostream>
#include <fstream>
#include "User.h"

int main()
{
	while (true) {
		String username = "username";
		String firstName = "First";
		String lastName = "Last";
		String password = "password";
		User u(username, password, firstName, lastName, 0);

		std::ofstream file("file.txt", std::ios::binary);
		u.SaveToFile(file);
		file.close();
		User u2;
		std::ifstream file2("file.txt", std::ios::binary);
		u2.ReadFromFile(file2);
		file2.close();
	}
}
