#include <string>
#include <iostream>
#include <fstream>

#include "product.h"
#include "shirt.h"
#include "pants.h"
#include "socks.h"
#include "underwear.h"
#include "shoes.h"
#include "hat.h"

#include "login.h"

int get_line_count(const std::string& path) {
	std::ifstream stream;
	stream.open(path);

	int count = 0;

	if (stream.is_open()) {
		std::string line;

		while (std::getline(stream, line)) {
			count++;
		}

		stream.close();
	}

	return count;
}

void write() {
	const std::string path = "Data/userinfo.csv";

	std::ofstream output;
	output.open(path);

	if (output.is_open()) {
		output << "Yo,Check,This,Out,!" << std::endl;
		std::cout << "Success!";
	}
	else {
		std::cout << "Failure...";
	}
}

//WHEN READING FROM FILE, NAME SECTIONS 'FIELD1', 'FIELD2', ETC.
//TO TURN EACH LINE INTO ITS CORRECT CLASS, DO A SWITCH CASE TO SEE IF FIELDS ARE EQUAL TO CERTAIN VALUES
//THEN STORE THEM AS THEIR CLASS INSIDE OF AN ARRAY OF PRODUCTS

product** read_storefront(const std::string& path, int count) {
	product** storefront = new product*[count];

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line;

		std::getline(stream, line); //skips header row

		for (int i = 0; i < count; i++) {

			std::getline(stream, line, ',');
			std::string clothing_type = line;

			std::getline(stream, line, ',');
			std::string brand = line;

			std::getline(stream, line, ',');
			double price = stod(line);

			std::getline(stream, line, ',');
			double rating = stod(line);

			bool char_detected = false;
			char char_field_one;
			double num_field_one = 0;

			std::getline(stream, line, ',');
			std::string temp = line;
			if (temp.length() == 1) {
				char new_temp = temp[0];
				if (new_temp == 'S' || new_temp == 'M' || new_temp == 'L' || new_temp == 'X') {
					char_field_one = new_temp;
					char_detected = true;
				}
				else {
					num_field_one = std::stod(temp);
					char_detected = false;
				}
			}
			else {
				num_field_one = std::stod(line);
				char_detected = false;
			}
			std::getline(stream, line, ',');
			double num_field_two = std::stod(line);

			std::getline(stream, line);
			int quantity = std::stoi(line);

			//std::getline(stream, line); //no comma because end of line
			//std::string checked_out = line;

			if (char_detected) {
				if (clothing_type == "underwear") {
					storefront[i] = new underwear(clothing_type, brand, price, rating, quantity, char_field_one, num_field_two);
				}
			}
			else {
				if (clothing_type == "shirt") {
					storefront[i] = new shirt(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two);
				}
				if (clothing_type == "pants") {
					storefront[i] = new pants(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two);
				}
				if (clothing_type == "socks") {
					storefront[i] = new socks(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two);
				}
				if (clothing_type == "shoes") {
					storefront[i] = new shoes(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two);
				}
				if (clothing_type == "hat") {
					storefront[i] = new hat(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two);
				}
			}
			

		}
		std::cout << "Successfully read storefront data." << std::endl;
		stream.close();

	}

	return storefront;

}

login* read_userinfo(const std::string& path, int count) {
	login* users = new login[count];

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line;

		std::getline(stream, line); //skips header row

		for (int i = 0; i < count; i++) {

			std::getline(stream, line, ',');
			std::string user = line;

			std::getline(stream, line, ',');
			std::string password = line;

			std::getline(stream, line);
			char is_admin = line[0];

			users[i] = login(user, password, is_admin);


		}
		std::cout << "Successfully read user information." << std::endl;
		stream.close();
	}
	return users;
}

login enter_password(login* users, int length, login user) {
	std::cout << "Please enter your password: ";
	std::string password;
	std::getline(std::cin, password);
	if (password == user.get_password()) {
		if (user.get_user() == "Karasu") {
			std::cout << "Welcome, creator! Have fun :D" << std::endl;
		}
		else if (user.get_is_admin() == 'Y') {
			std::cout << "Welcome, Admin " << user.get_user() << "!" << std::endl;
		}
		else {
			std::cout << "Welcome, " << user.get_user() << "!" << std::endl;
		}
		return user;
	}
	std::cout << "Incorrect password. Please try again." << std::endl;
	return enter_password(users, length, user);
}
//i had to swap these two functions around to get this to work. thanks, c++
login enter_username(login* users, int length) {
	std::cout << "Please enter your username: ";
	std::string username;
	std::getline(std::cin, username);
	bool userfound = false;
	for (int i = 0; i < length; i++) {
		if (username == users[i].get_user()) {
			login user = users[i];
			userfound == true;
			login confirm = enter_password(users, length, user);
			return confirm;
		}
	}
	std::cout << "User not found. Please try again." << std::endl;
	enter_username(users, length);
}




int main() {
	const std::string path = "Data/products.csv";
	int file_length = get_line_count(path)-1;

	const std::string userinfo = "Data/userinfo.csv";
	int user_count = get_line_count(userinfo) - 1;

	login* users = read_userinfo(userinfo, user_count);

	product** storefront = read_storefront(path, file_length);

	login current_user = enter_username(users, user_count);

	if (current_user.get_user() == "Karasu") {
		std::cout << "Now printing all user info for super admin level:" << std::endl;
		for (int i = 0; i < user_count; i++) {
			if (users[i].get_is_admin() != 'C') {
				std::cout << "Username: " << users[i].get_user() << " | Password: " << users[i].get_password() << std::endl;
			}
		}
	}

	if (current_user.get_is_admin() == 'Y' || current_user.get_is_admin() == 'C') {
		std::cout << "Would you like to print out the store's current inventory? Y or N please. ";
		std::string confirm;
		std::getline(std::cin, confirm);
		if (confirm == "Y") {
			for (int i = 0; i < file_length; i++) {
				storefront[i]->print();
			}
		}
		else if (confirm == "N") {
			std::cout << "Alright. Take care, Admin " << current_user.get_user();
		}
		else {
			std::cout << "I didn't quite get that. Please try again later.";
		}
	}
	else {
		std::cout << "The storefront is currently down. Please check again later.";
	}

	//CLEAN UP
	for (int i = 0; i < file_length; i++) {
		delete storefront[i];
	}
	//clean up is unecessary for users because it doesnt use new, and the one part that does is deconstructed out of scope
	return 0;
}
