#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cctype>
#include <list>
#include <typeinfo>
#include <sstream>
#include <random>
//Colin, DM me if you have questions about any of the code. I've been working on this for like 7 hours today and I'm suffering from brain damage. See you soon <3
#include "product.h"
#include "shirt.h"
#include "pants.h"
#include "socks.h"
#include "underwear.h"
#include "shoes.h"
#include "hat.h"

#include "login.h"

std::vector<product*> read_store(const std::string& path) {
	std::vector<product*> storefront;
	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line;

		std::getline(stream, line); //skips header row

		for (;;) { //forever loop
			if (stream.eof()) { //checks if there is no more lines
				std::cout << "Successfully read storefront data." << std::endl;
				stream.close();
				return storefront;
			}
			std::getline(stream, line, ',');
			std::string clothing_type = line;

			std::getline(stream, line, ',');
			std::string brand = line;

			std::getline(stream, line, ',');
			double price = stod(line);

			std::getline(stream, line, ',');
			double rating = stod(line);

			char char_field_one='a';
			double num_field_one = 0;	//creates distinction between underwear's first field and all other first fields

			std::getline(stream, line, ',');
			std::string temp = line;
			if (temp.length() == 1) {	//checks to see if the taken string is only one character
				char new_temp = temp[0];
				if (new_temp == 'S' || new_temp == 'M' || new_temp == 'L' || new_temp == 'X') {	//verifies that its a valid underwear size/not just a single digit number
					char_field_one = new_temp;
				}
				else {
					num_field_one = std::stod(temp);	//will throw an exception if a letter character sneaks in, but this shouldn't happen if file is correct
				}
			}
			else {
				num_field_one = std::stod(line);	//all other clothing types will fall in here
			}
			std::getline(stream, line, ',');
			double num_field_two = std::stod(line);

			std::getline(stream, line, ',');
			int quantity = std::stoi(line);

			std::getline(stream, line);
			int reserved = std::stoi(line);

			//BIG if else chain, would love to simplify with switch but...doesn't work with string and i dont want to try enum rn...
				if (clothing_type == "shirt") {
					storefront.push_back(new shirt(clothing_type, brand, price, rating, quantity, reserved, num_field_one, num_field_two));
				}
				if (clothing_type == "pants") {
					storefront.push_back(new pants(clothing_type, brand, price, rating, quantity, reserved, num_field_one, num_field_two));
				}
				if (clothing_type == "socks") {
					storefront.push_back(new socks(clothing_type, brand, price, rating, quantity, reserved, num_field_one, num_field_two));
				}
				if (clothing_type == "underwear") {
					storefront.push_back(new underwear(clothing_type, brand, price, rating, quantity, reserved, char_field_one, num_field_two));
				}
				if (clothing_type == "shoes") {
					storefront.push_back(new shoes(clothing_type, brand, price, rating, quantity, reserved, num_field_one, num_field_two));
				}
				if (clothing_type == "hat") {
					storefront.push_back(new hat(clothing_type, brand, price, rating, quantity, reserved, num_field_one, num_field_two));
				}

				//below lines are for printing for verification
				/*std::cout << clothing_type << ", " <<
					brand << ", " <<
					price << ", " <<
					rating << ", ";
					if (clothing_type == "underwear") { char_field_one; } else {num_field_one;}
					std::cout << ", " <<
					num_field_two << ", " <<
					quantity << ", " << std::endl;*/

		}
	}
	else {	//throws exception to stop program from breaking without a correct file
		std::cout << "Failed to read from file--aborting proccess!";
		throw std::exception("Failed to read from designated file");
	}
}
enum class admin_status {
	N,
	Y,
	C
};
char admin_to_char(admin_status a) {
	switch (a) {
	case admin_status::N: return 'N';
	case admin_status::Y: return 'Y';
	case admin_status::C: return 'C';
	}
}
std::vector<login> read_userinfo(const std::string& path) {
	std::vector<login> users;

	std::ifstream stream;
	stream.open(path);

	if (stream.is_open()) {
		std::string line;

		std::getline(stream, line); //skips header row

		for (;;) {
			if (stream.eof()) {
				std::cout << "Successfully read user information." << std::endl;
				stream.close();
				return users;
			}
			std::getline(stream, line, ',');
			std::string user = line;

			std::getline(stream, line, ',');
			std::string password = line;

			std::getline(stream, line);
			admin_status admin = static_cast<admin_status>(line[0]);	//this converts the character N/Y/C into the admin status enum
			//THE ENTIRE THING WAS SOLVED VIA STATIC CAST GOD DAMMIT
			users.push_back(login(user, password, admin_to_char(admin)));	//admin to char will return N/Y/C which can be read for the login object
			//and yes, I know, it was easier with just getting a character, but...i have to prove knowledge of enums so...
		}
	}
	else {	//throws exception to prevent program from breaking
		std::cout << "Failed to read from file--aborting proccess!";
		throw std::exception("Failed to read from designated file");
	}
}

login enter_password(std::vector<login> users, login user) {
	std::cout << "Please enter your password: ";
	std::string password;
	std::getline(std::cin, password);
	if (password == user.get_password()) {
		if (user.get_user() == "Karasu" || user.get_user() == "Colin") {
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
	return enter_password(users, user);
}

login enter_username(std::vector<login> users) {
	std::cout << "Please enter your username: ";
	std::string username;
	std::getline(std::cin, username);
	if (username.length() == 0) {
		std::cout << "User not found. Please try again." << std::endl;
		return enter_username(users);
	}
	else {
		for (int i = 0; i < users.size(); i++) {
			if (username == users[i].get_user()) {
				login user = users[i];
				login confirm = enter_password(users, user);
				return confirm;
			}
		}
		std::cout << "User not found. Please try again." << std::endl;
		return enter_username(users);
	}
	
}

void create_account(std::vector<login>& users) {
	std::cout << "Please enter the username you want to use. It can't be less than three characters, or more than 20." << std::endl;
	bool valid_username = false;
	bool unique_username = false;
	std::string new_username;
	while (valid_username == false&&unique_username==false) {	//continueously checks if the username is valid and unique
		std::getline(std::cin, new_username);
		if (new_username.length() < 3) {
			std::cout << "Your username must be at least 3 characters! Please enter a valid username." << std::endl;
			return create_account(users);
		}
		else {
			valid_username = true;
		}
		for (int i = 0; i < users.size(); i++) {
			if (users[i].get_user() == new_username) {
				std::cout << "This username is already in use! Please try again." << std::endl;
				return create_account(users);
			}
			if (i == users.size()) {
				unique_username = true;
			}
		}
	}
	std::cout << "Alright, " << new_username << ", please enter a password. It must be 6-25 characters." << std::endl;
	bool valid_password = false;
	while (valid_password == false) {	//continueously checks if the password is valid
		std::string new_password;
		std::getline(std::cin, new_password);
		if (new_password.length() < 6) {
			std::cout << "Your password must be at least 6 characters! Please enter a valid password." << std::endl;
		}
		else {
			users.push_back(login(new_username, new_password, 'N'));
			std::cout << "Awesome! Please log in with your information now." << std::endl;
			valid_password = true;
		}
	}
}

void add_product(std::vector<product*> store) {
	std::string clothing_type;
	std::string brand;
	std::string get_price;
	double price = 0;
	std::string get_rating;
	double rating = -1;
	std::string get_field_one;
	char underwear_size = 'a';
	char valid_char = 'a';
	double field_one = 0;
	std::string get_field_two;
	double field_two = 0;
	std::string get_quantity;
	int quantity = -1;

	std::cout << "What clothing type is this product? Remember to use lowercase: ";
	std::getline(std::cin, clothing_type);
	if (clothing_type == "shirt" || clothing_type == "pants" || clothing_type == "socks" || clothing_type == "underwear" || clothing_type == "shoes" || clothing_type == "hat") {

		while (brand.length() < 1 || brand.length() > 20) {
			std::cout << "What is the brand name? Remember that it must be between 1-20 characters: ";
			std::getline(std::cin, brand);
			if (brand == "menu") {
				return;
			}
			else if (brand.length() < 1 || brand.length() > 20) {
				std::cout << "1-20 characters, please!" << std::endl << std::endl;
			}
		}
		while (price < 10 || price > 10000) {
			std::cout << "What is the price for the clothes? Remember that it must be between $10-$10000: ";
			std::getline(std::cin, get_price);
			if (get_price == "menu") {
				return;
			}
			//oh you can parse strings as streams, interesting. using this to verify that the input is a valid double
			//(because checking if everything is a digit with a double using a decimal point will fail)
			std::istringstream check_string(get_price);
			double check;
			check_string >> std::noskipws >> check;
			if (check_string.eof() && check_string.fail() == false) {
				price = stod(get_price);
				if (price < 10 || price > 10000) {
					std::cout << "10-10000, please!" << std::endl << std::endl;
				}
			}
			else {
				std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
			}
		}
		while (rating < 0 || rating > 5) {
			std::cout << "What is the rating for the clothes?";
			std::getline(std::cin, get_rating);
			if (get_rating == "menu") {
				return;
			}
			std::istringstream check_string(get_rating);
			double check;
			check_string >> std::noskipws >> check;
			if (check_string.eof() && check_string.fail() == false) {
				rating = stod(get_rating);
				if (rating < 0 || rating > 5) {
					std::cout << "0-5, please!" << std::endl << std::endl;
				}
			}
			else {
				std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
			}
		}
		//field one below
		if (clothing_type == "shirt") {
			while (field_one < 14 && field_one > 20) {
				std::cout << "What is the collar size? Reminder that it must be between 14-20: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					return;
				}
				std::istringstream check_string(get_field_one);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_one = stod(get_field_one);
					if (field_one < 14 || field_one > 20) {
						std::cout << "14-20, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "pants") {
			while (field_one < 27 && field_one > 44) {
				std::cout << "What is the waist size? Reminder that it must be between 27-44: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					return;
				}
				std::istringstream check_string(get_field_one);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_one = stod(get_field_one);
					if (field_one < 27 || field_one > 44) {
						std::cout << "27-44, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "socks") {
			while (field_one < 3 && field_one > 10) {
				std::cout << "What is the sock height? Reminder that it must be between 3-10: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					return;
				}
				std::istringstream check_string(get_field_one);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_one = stod(get_field_one);
					if (field_one < 3 || field_one > 10) {
						std::cout << "3-10, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "underwear") {
			while (underwear_size == 'a') {
				std::cout << "What is the size of the underwear? Reminder to use S/M/L/X only: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					return;
				}
				if (get_field_one.length() == 1) {	//checks to see if the taken string is only one character
					valid_char = get_field_one[0];
					if (valid_char == 'S' || valid_char == 'M' || valid_char == 'L' || valid_char == 'X') {	//verifies that its a valid underwear size/not just a single digit number
						underwear_size = valid_char;
					}
					else {
						std::cout << "S/M/L/X only, please!" << std::endl << std::endl;
					}
				}
			}
		}
		if (clothing_type == "shoes") {
			while (field_one < 2.5 && field_one > 5) {
				std::cout << "What is the shoe width? Reminder that it must be between 2.5-5: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					return;
				}
				std::istringstream check_string(get_field_one);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_one = stod(get_field_one);
					if (field_one < 2.5 || field_one > 5) {
						std::cout << "2.5-5, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "hat") {
			while (field_one < 3 && field_one > 8) {
				std::cout << "What is the hat height? Reminder that it must be between 3-8: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					return;
				}
				std::istringstream check_string(get_field_one);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_one = stod(get_field_one);
					if (field_one < 3 || field_one > 8) {
						std::cout << "3-8, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		//field two below
		if (clothing_type == "shirt") {
			while (field_two < 32 && field_two > 38) {
				std::cout << "What is the sleeve length? Reminder that it must be between 32-38: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					return;
				}
				std::istringstream check_string(get_field_two);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_two = stod(get_field_two);
					if (field_two < 32 || field_two > 38) {
						std::cout << "32-38, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "pants") {
			while (field_two < 32 && field_two > 51) {
				std::cout << "What is the hip length? Reminder that it must be between 32-51: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					return;
				}
				std::istringstream check_string(get_field_two);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_two = stod(get_field_two);
					if (field_two < 32 || field_two > 51) {
						std::cout << "32-51, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "socks") {
			while (field_two < 3 && field_two > 14) {
				std::cout << "What is the sock length? Reminder that it must be between 3-14: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					return;
				}
				std::istringstream check_string(get_field_two);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_two = stod(get_field_two);
					if (field_two < 3 || field_two > 14) {
						std::cout << "3-14, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				};
			}
		}
		if (clothing_type == "underwear") {
			while (field_two < 24 && field_two > 40) {
				std::cout << "What is the trunk size? Reminder that it must be between 24-40: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					return;
				}
				std::istringstream check_string(get_field_two);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_two = stod(get_field_two);
					if (field_two < 24 || field_two > 40) {
						std::cout << "24-40, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "shoes") {
			while (field_two < 9 && field_two > 12.5) {
				std::cout << "What is the shoe length? Reminder that it must be between 9-12.5: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					return;
				}
				std::istringstream check_string(get_field_two);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_two = stod(get_field_two);
					if (field_two < 9 || field_two > 12.5) {
						std::cout << "9-12.5, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		if (clothing_type == "hat") {
			while (field_two < 20 && field_two > 25) {
				std::cout << "What is the brim width? Reminder that it must be between 20-25: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					return;
				}
				std::istringstream check_string(get_field_two);
				double check;
				check_string >> std::noskipws >> check;
				if (check_string.eof() && check_string.fail() == false) {
					field_two = stod(get_field_two);
					if (field_two < 20 || field_two > 25) {
						std::cout << "20-25, please!" << std::endl << std::endl;
					}
				}
				else {
					std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
				}
			}
		}
		while (quantity < 0 || quantity>100) {
			std::cout << "How many of these are left in stock? ";
			std::getline(std::cin, get_quantity);
			if (get_quantity == "menu") {
				return;
			}
			if (std::all_of(get_quantity.begin(), get_quantity.end(), std::isdigit)) {
				quantity = stoi(get_quantity);
			}
			else {
				std::cout << "Please input a valid number! Integers only, please." << std::endl << std::endl;
			}
		}

		if (clothing_type == "shirt") {
			store.push_back(new shirt(clothing_type, brand, price, rating, quantity, 0, field_one, field_two));
		}
		if (clothing_type == "pants") {
			store.push_back(new pants(clothing_type, brand, price, rating, quantity, 0, field_one, field_two));
		}
		if (clothing_type == "socks") {
			store.push_back(new socks(clothing_type, brand, price, rating, quantity, 0, field_one, field_two));
		}
		if (clothing_type == "underwear") {
			store.push_back(new underwear(clothing_type, brand, price, rating, quantity, 0, underwear_size, field_two));
		}
		if (clothing_type == "shoes") {
			store.push_back(new shoes(clothing_type, brand, price, rating, quantity, 0, field_one, field_two));
		}
		if (clothing_type == "hat") {
			store.push_back(new hat(clothing_type, brand, price, rating, quantity, 0, field_one, field_two));
		}
		std::cout << std::endl << std::endl;
		store.at(store.size() - 1)->print();
		std::cout << "Okay! Did that product look correct? Y/y or N/n only, please: ";
		bool valid_yn = false;
		std::string confirm = "a";
		while (valid_yn == false) {
			std::getline(std::cin, confirm);
			if (confirm == "menu") {
				return;
			}
			if (confirm == "y" || confirm == "Y") {
				std::cout << std::endl << "Awesome! Your product has been successfully added to the storefront!" << std::endl << std::endl;
				valid_yn == true;
			}
			else if (confirm == "n" || confirm == "N") {
				std::cout << std::endl << std::endl << "Okay, I'll delete the product. Would you like to try to add a new product? ";
				store.pop_back();
				std::getline(std::cin, confirm);
				if (confirm == "menu") {
					return;
				}
				if (confirm == "y" || confirm == "Y") {
					std::cout << std::endl << std::endl << "Alright, let's take it from the top!" << std::endl << std::endl;
					valid_yn == true;
					return add_product(store);
				}
				else if (confirm == "n" || confirm == "N") {
					std::cout << std::endl << std::endl << "Okay, no worries." << std::endl << std::endl;
					valid_yn == true;
					return;
				}
				else {
					std::cout << std::endl << std::endl << "I didn't quite get that. Would you like to try to add a new product? Y/y or N/n only, please. ";
				}
			}
			else {
				std::cout << std::endl << std::endl << "I didn't quite get that. Did that product look correct? Y/y or N/n only, please. ";
			}
		}
	}
	else if (clothing_type == "menu") {
		return;
	}
	else {
		std::cout << "Please input 'shirt', 'pants', 'socks', 'underwear', 'shoes', or 'hat'!" << std::endl;
		return add_product(store);
	}
}


void write_to_storefront(std::vector<product*> store) {
	const std::string path = "Data/products.csv";

	std::ofstream output;
	output.open(path);

	if (output.is_open()) {
		output << "Clothing type,Brand,Price,Rating,Field one,Field two,Quantity" << std::endl;
		for (int i = 0; i < store.size(); i++) {
			output << store[i]->get_clothing_type() << ",";
			output << store[i]->get_brand() << ",";
			output << store[i]->get_price() << ",";
			output << store[i]->get_rating() << ",";
			//LONG IF ELSE CHAIN PLEASE CHECK IF THIS CAN BE SIMPLIFIED
			if (shirt* shirtptr = dynamic_cast<shirt*>(store[i])) {
				output << shirtptr->get_collar_size() << ",";
			}
			else if (pants* pantsptr = dynamic_cast<pants*>(store[i])) {
				output << pantsptr->get_waist_size() << ",";
			}
			else if (socks* socksptr = dynamic_cast<socks*>(store[i])) {
				output << socksptr->get_sock_height() << ",";
			}
			else if (underwear* underwearptr = dynamic_cast<underwear*>(store[i])) {
				output << underwearptr->get_underwear_size() << ",";
			}
			else if (shoes* shoesptr = dynamic_cast<shoes*>(store[i])) {
				output << shoesptr->get_shoe_width() << ",";
			}
			else if (hat* hatptr = dynamic_cast<hat*>(store[i])) {
				output << hatptr->get_hat_height() << ",";
			}
			//SAME FOR THIS ONE
			if (shirt* shirtptr = dynamic_cast<shirt*>(store[i])) {
				output << shirtptr->get_sleeve_length() << ",";
			}
			else if (pants* pantsptr = dynamic_cast<pants*>(store[i])) {
				output << pantsptr->get_hip_length() << ",";
			}
			else if (socks* socksptr = dynamic_cast<socks*>(store[i])) {
				output << socksptr->get_sock_length() << ",";
			}
			else if (underwear* underwearptr = dynamic_cast<underwear*>(store[i])) {
				output << underwearptr->get_trunk_size() << ",";
			}
			else if (shoes* shoesptr = dynamic_cast<shoes*>(store[i])) {
				output << shoesptr->get_shoe_length() << ",";
			}
			else if (hat* hatptr = dynamic_cast<hat*>(store[i])) {
				output << hatptr->get_brim_width() << ",";
			}
			output << store[i]->get_quantity() << ',';
			output << store[i]->get_reserved();
			if (i != store.size() - 1) {//prevents issue with extra line breaking program
				output << std::endl;	
			}
		}
		std::cout << "Storefront information saved." << std::endl;
	}
	else {
		std::cout << "Failed to write to file...Data may have been lost.";
	}
}

void write_to_user_info(std::vector<login> users) {
	const std::string path = "Data/userinfo.csv";

	std::ofstream output;
	output.open(path);

	if (output.is_open()) {
		output << "Username,Password,is_admin" << std::endl;
		for (int i = 0; i < users.size(); i++) {
			output << users[i].get_user() << ",";
			/*std::cout << users[i].get_user() << " ";*/
			output << users[i].get_password() << ",";
			/*std::cout << users[i].get_password() << " ";*/
			output << users[i].get_is_admin();
			/*std::cout << users[i].get_is_admin() << std::endl;*/
			if (i!=users.size()-1) {//prevents issue with extra line breaking program
				output << std::endl;	
			}
		}
		std::cout << "Users information saved." << std::endl;
	}
	else {
		std::cout << "Failed to save user information...Data may have been lost--contact an administrator!" << std::endl;
	}
}

//int main() {
//	const std::string path = "Data/products.csv";
//
//	const std::string userinfo = "Data/userinfo.csv";
//
//	std::vector<login> users = read_userinfo(userinfo);
//
//	std::vector<product*> store = read_store(path);
//	//asks for login info, if no, asks for account creation. make this a function maybe?
//	login current_user;
//	std::cout << "Do you currently have an account? Y/y or N/n: ";
//	std::string account_confirm;
//	std::getline(std::cin, account_confirm);
//	if (account_confirm == "Y" || account_confirm == "y") {
//		current_user = enter_username(users);
//	}
//	else if (account_confirm == "N" || account_confirm == "n") {
//		std::cout << "Okay, would you like to create an account? ";
//		std::string confirm;
//		std::getline(std::cin, confirm);
//		if (confirm == "Y" || confirm == "y") {
//			create_account(users);
//			current_user = enter_username(users);
//		}
//		else if (confirm == "N" || confirm == "n") {
//			std::cout << "Okay! Enjoy your visit!" << std::endl;
//			current_user = login("Default", "qqqqqq", 'N');
//		}
//	}
//	else {
//		std::cout << "I couldn't get that, please try again another time.";	//make this a function so this line changes to 'please input a valid character' or something
//	}
//
//	if (current_user.get_is_admin() == 'C') {//if its one of us, prints out all user info. we can be trusted...maybe (:
//		std::cout << "Now printing all user info for super admin level:" << std::endl;
//		for (int i = 0; i < users.size(); i++) {
//			if (users[i].get_is_admin() != 'C') {
//				std::cout << "Username: " << users[i].get_user() << " | Password: " << users[i].get_password() << std::endl;
//			}
//		}
//	}
//	//asks to print out storefront. eventually this will be a function
//		std::cout << "Would you like to print out the store's current inventory? Y or N please. ";
//		std::string confirm;
//		std::getline(std::cin, confirm);
//		if (confirm == "Y") {
//			for (int i = 0; i < store.size(); i++) {
//				store[i]->print();
//			}
//		}
//		else if (confirm == "N") {
//			if (current_user.get_user() == "Default") {
//				std::cout << "Alright. Take care." << std::endl;
//			}
//			else {
//				std::cout << "Alright. Take care, " << current_user.get_user() << std::endl;
//			}
//		}
//		else {
//			std::cout << "I didn't quite get that. Please try again later.";
//		}
//	//updates the files, in case data has been changed
//	write_to_storefront(store);
//	write_to_user_info(users);
//
//	//CLEAN UP
//	for (int i = 0; i < store.size(); i++) {
//		delete store[i];
//	}
//	//clean up is unecessary for users because it doesnt use new
//	return 0;
//}

int main() {
	const std::string path = "Data/products.csv";

	const std::string userinfo = "Data/userinfo.csv";

	std::vector<login> users = read_userinfo(userinfo);

	std::vector<product*> store = read_store(path);

	login current_user("None", "aaaaaa", 'N');

	char command='0';

	std::cout << "--Welcome to Crow's Nest Clothing!--" << std::endl;

	while (command != 'q') {
		std::cout << "Avalible commands:" << std::endl;
		std::cout << "[P/p]: Print out all products" << std::endl;
		std::cout << "[F/f]: Filter products by specified criteria" << std::endl;
		std::cout << "[S/s]: Sort storefront data by specified criteria" << std::endl;
		if (current_user.get_user() == "None") {
			std::cout << "[L/l]: Login" << std::endl;
			std::cout << "[C/c]: Create account" << std::endl;
		}
		if (current_user.get_user() != "None") {
			std::cout << "[B/b]: Buy a product" << std::endl;
			std::cout << "[R/r]: Reserve a product in your shopping cart" << std::endl;
			std::cout << "[V/v]: View products in your shopping cart" << std::endl;
		}
		if (current_user.get_is_admin() != 'N' ) {
			std::cout << "---Admin functions---" << std::endl;
			std::cout << "[A/a]: Add a new product to the storefront" << std::endl;
			std::cout << "[E/e]: Edit fields for current products" << std::endl;
			std::cout << "---------------------" << std::endl;

		}
		if (current_user.get_is_admin() == 'C') {
			std::cout << "---Program creator functions---" << std::endl;
			std::cout << "[U/u]: Print out all user data" << std::endl;
			std::cout << "[D/d]: Delete account" << std::endl;
			std::cout << "-------------------------------" << std::endl;
		}
		if (current_user.get_user() != "None") {
			std::cout << "[O/o]: Log out of your account" << std::endl;
		}
		std::cout << "[Q/q]: Quit the program" << std::endl << std::endl;
		std::cout << "Reminder that at any point, you can type out 'menu' to return to this menu." << std::endl << std::endl;
		std::cout << "What function would you like to access? ";

		std::string get_command;
		std::getline(std::cin, get_command);
		if (get_command == "ACTIVATEFULLOVERIDE") {	//uuuhhhh....idk what this is doing here lol
			std::mt19937 generator(std::random_device{}());
			std::uniform_int_distribution<int> distribution(1, 100000000000);
			std::cout << "Alright! Here we go! MAMIMUM FORCE ON!!!" << std::endl << std::endl;
			for (int i = 0; i < 3000; i++) {
				int jargon = distribution(generator);
				std::cout << jargon << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAA" << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAA" << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNN" << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNNNNNNNNNN" << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNNNNNNNNNNDDDDDD" << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNNNNNNNNNNDDDDDDDDDDDDDDD" << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNNNNNNNNNNDDDDDDDDDDDDDDD........." << std::endl;
			}
			for (int i = 0; i < 300; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNNNNNNNNNNDDDDDDDDDDDDDDD.................." << std::endl;
			}
			for (int i = 0; i < 100; i++) {
				std::cout << "AAAAAAAAAAAAAANNNNNNNNNNNNNNDDDDDDDDDDDDDDD................................" << std::endl << std::endl;
			}
			std::cout << R"(
 __      __
( _\    /_ )
 \ _\  /_ / 
  \ _\/_ /_ _
  |_____/_/ /|
  (  (_)__)J-)
  (  /`.,   /
   \/  ;   /
    | === |

Goodbye! ^-^

)";
			throw std::exception("See ya later! <3 ~Karasu and Colin, Crow's Nest's Managers");
		}
		std::transform(get_command.begin(), get_command.end(), get_command.begin(), ::toupper);	//this turns all lowercase to uppercase
		command = get_command[0];
		std::cout << std::endl;

		switch (command) {
		case 'P': {
			for (int i = 0; i < store.size(); i++) {
				store[i]->print();
			}
			std::cout << std::endl;
			break;
		}
		case 'F': {
			bool valid_state = false;
			while (valid_state == false) {
				std::cout << "Availible filters:" << std::endl;
				std::cout << "[T/t] for clothing type, [B/b] for brand, [S/s] for clothing currently in stock, or [P/p] to set price range: ";
				std::getline(std::cin, get_command);
				if (get_command == "menu") {
					break;
				}
				std::transform(get_command.begin(), get_command.end(), get_command.begin(), ::toupper);
				command = get_command[0];

				switch (command) {
				case 'T':
				{
					std::cout << "Which clothing type would you like to search for?" << std::endl;
					std::cout << "[S/s] for shirt, [P/p] for pants, [T/t] for socks, [U/u] for underwear, [V/v] for shoes, or [H/h] for hat: ";
					std::getline(std::cin, get_command);
					if (get_command == "menu") {
						break;
					}
					std::transform(get_command.begin(), get_command.end(), get_command.begin(), ::toupper);
					command = get_command[0];
					std::cout << std::endl;
					switch (command) {
					case 'S':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (shirt* print_shirt = dynamic_cast<shirt*>(p)) {
								print_shirt->print();
							}});
							std::cout << std::endl;
							break;
					case 'P':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (pants* print_pants = dynamic_cast<pants*>(p)) {
								print_pants->print();
							}});
							std::cout << std::endl;
							break;
					case 'T':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (socks* print_socks = dynamic_cast<socks*>(p)) {
								print_socks->print();
							}});
							std::cout << std::endl;
							break;
					case 'U':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (underwear* print_underwear = dynamic_cast<underwear*>(p)) {
								print_underwear->print();
							}});
							std::cout << std::endl;
							break;
					case 'V':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (shoes* print_shoes = dynamic_cast<shoes*>(p)) {
								print_shoes->print();
							}});
							std::cout << std::endl;
							break;
					case 'H':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (hat* print_hat = dynamic_cast<hat*>(p)) {
								print_hat->print();
							}});
							std::cout << std::endl;
							break;
					default:
						std::cout << "Please enter a valid character!" << std::endl << std::endl;
						break;
					}
					break;
				}
				case 'B':
				{
					std::cout << "What brand would you like to search for? ";
					std::string brand_search;
					std::getline(std::cin, brand_search);
					if (brand_search == "menu") {
						break;
					}
					std::cout << std::endl;
					std::for_each(store.begin(), store.end(), [&brand_search](product*& p) {
						if (p->get_brand() == brand_search) {
							p->print();
						}
						});
					std::cout << std::endl;
					break;
				}
				case 'S':
				{
					std::cout << std::endl;
					std::for_each(store.begin(), store.end(), [](product*& p) {
						if (p->get_reserved() < p->get_quantity()) {
							p->print();
						}
						});
					std::cout << std::endl;
					break;
				}
				case 'P':
				{
					double min_price = -1;
					double max_price = 10001;
					std::string temp;
					while (min_price < 0) {
						std::cout << "Please enter the minimum price you'd like to search for: ";
						std::getline(std::cin, temp);
						if (temp == "menu") {
							break;
						}
						if (std::all_of(temp.begin(), temp.end(), std::isdigit)) {
							min_price = stod(temp);
							if (min_price < 0 || min_price>10000) {
								std::cout << "Please enter a value greater than 0 and less than 10000!" << std::endl << std::endl;

							}
						}
						else {
							std::cout << "Please enter a numeric value!" << std::endl << std::endl;
						}
					}
					while (max_price > 10000) {
						std::cout << "Please enter the maximum price you'd like to search for: ";
						std::getline(std::cin, temp);
						if (temp == "menu") {
							break;
						}
						if (std::all_of(temp.begin(), temp.end(), std::isdigit)) {
							max_price = stod(temp);
							if (max_price < 0 || max_price>10000) {
								std::cout << "Please enter a value greater than 0 and less than 10000!" << std::endl << std::endl;
							}
							else if (min_price > max_price) {
								std::cout << std::endl << "Inputted maximum price is less than minimum price, swapping the values for the search." << std::endl;
								double temp_double = min_price;
								min_price = max_price;
								max_price = temp_double;
							}
						}
						else {
							std::cout << "Please enter a numeric value!" << std::endl << std::endl << std::endl;
						}
					}
					std::cout << std::endl << "Clothes we have between $" << min_price << " and $" << max_price << ":" << std::endl << std::endl;
					std::vector<product*> temp_sort;
					std::for_each(store.begin(), store.end(), [&max_price, &min_price, &temp_sort](product*& p) {
						if (p->get_price() <= max_price && p->get_price() >= min_price) {
							temp_sort.push_back(p);
						}
						}
					);
					std::sort(temp_sort.begin(), temp_sort.end(), [](product*& p1, product*& p2) {
						return p1->get_price() < p2->get_price();
						});
					std::for_each(temp_sort.begin(), temp_sort.end(), [](product*& p) {
						p->print();
						});
					break;
				}
				default:
					std::cout << std::endl << "Please enter a valid character!" << std::endl << std::endl;
				}
			}
			break;
		}
		case 'S'://sort data
			break;
		case 'L'://login (not logged in)
			if (current_user.get_user() == "None") {
				current_user = enter_username(users);
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'C'://create account (not logged in)
			if (current_user.get_user() == "None") {
				create_account(users);
				current_user = enter_username(users);
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'B'://buy product (logged in)
			if (current_user.get_user() != "None") {
				//buy product code goes here
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'R'://reserve product (logged in)
			if (current_user.get_user() != "None") {
				//reserve product code goes here
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'V'://view reserved products (logged in)
			if (current_user.get_user() != "None") {
				//view reserved products code goes here
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'A'://add item (admin)
			if (current_user.get_is_admin() == 'Y' || current_user.get_is_admin() == 'C') {
				{
					std::cout << "Alright, let's do this!" << std::endl << std::endl;
					add_product(store);
				}
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'E'://edit item (admin)
			if (current_user.get_is_admin() == 'Y' || current_user.get_is_admin() == 'C') {
				//edit item code goes here
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;		
		case 'U'://print all users (creator)
			if (current_user.get_is_admin() == 'C') {
				{
					std::cout << "Now printing all user info for super admin level:" << std::endl;
					for (int i = 0; i < users.size(); i++) {
						if (users[i].get_is_admin() != 'C') {
							std::cout << "Username: " << users[i].get_user() << " | Password: " << users[i].get_password() << std::endl;
						}
					}
					std::cout << std::endl;
				}
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'D'://delete an account (creator)
			if (current_user.get_is_admin() == 'C') {
			{
			for (int i = 0; i < users.size(); i++) {
				if (users[i].get_is_admin() != 'C') {
					std::cout << "Username: " << users[i].get_user() << " | Password: " << users[i].get_password() << std::endl;
				}
			}
			std::cout << std::endl << "Which account would you like to delete?" << std::endl;
			std::string dlt_account;
			std::getline(std::cin, dlt_account);
			if (dlt_account == "menu") {
				break;
			}
			else if (dlt_account.length() >= 3 && dlt_account.length() <= 20) {
				/*std::for_each(users.begin(), users.end(), [&dlt_account, &users](const login& l) {
					int position = std::distance(users.begin(),)
					if (l.get_user() == dlt_account) {
						users.erase();
					}
					});*/			//I tried using this but realized it was really hard to get the iterator's position, so I just went with a index for loop
					/*for (int i = 0; i < users.size(); i++) {

						if (users[i].get_user() == dlt_account) {
							account_found == true;
						}
						if (users[i].get_user() != dlt_account && account_found==false) {
							it++;
						}

						}*/
				std::vector<login>::iterator it = users.begin();
				int i = 0;
				while (i < users.size()) {
					if (users[i].get_user() == dlt_account) {
						break;
					}
					if (users[i].get_user() != dlt_account) {
						it++;
					}
					i++;
				}
				if (i == users.size()) {
					std::cout << std::endl << "No user named " << dlt_account << " exists! Unable to delete.";
				}
				else {
					login test_user = *it;
					if (test_user.get_is_admin() == 'C') {
						std::cout << std::endl << "Hey wait a moment! You're trying to remove a hidden creator account. Are you /sure/ you want to do this? If so, type YES in all caps: ";
						std::string accept_deletion;
						std::getline(std::cin, accept_deletion);
						if (accept_deletion == "menu") {
							break;
						}
						else if (accept_deletion == "YES") {
							users.erase(it);
							std::cout << std::endl << "Successfully deleted user " << test_user.get_user() << ".";
						}
						else {
							std::cout << std::endl << "Alright, thanks for keeping the account safe.";
						}
					}
					else {
						users.erase(it);
						std::cout << std::endl << "Successfully deleted user " << test_user.get_user() << ".";
					}
				}
			}
			else {
				std::cout << "Unable to search given name--Username must be between 3-20 characters.";
			}
			//THAT WAS THE WORST TWO HOURS IVE CODED IN A WHILE WTH
			//In the end, I settled on an incrementing while loop, breaking when the value of users[i] was the same as the user specified string
			//I was getting crazy errors when trying to get user at position [it] which makes sense, since its an iterator and not a specified position
			//I was also getting errors due to me forgetting to increment 'i' at first
			//Finally, I erase at position 'it', which is the iterated location.
			std::cout << std::endl << std::endl;
			}
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'O'://log out
			if (current_user.get_user() != "None") {
				current_user = login("None", "aaaaaa", 'N');
				std::cout << std::endl << "Logged out successfully." << std::endl << std::endl;
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'Q': {
			std::cout << std::endl << "Alright. Thank you for visiting Crow's Nest Clothing! Have a great day ^-^";
			//ascii art my beloved--adapted from https://www.asciiart.eu/animals/birds-land : Parrot by Morfina
			std::cout << R"(

                           .
                          | \/|
  (\   _                  ) )|/|	  /-----|
      (/            _----. /.'.'	 /	|
.-._________..      .' ^ _\  .'		< Craw!	|	
'.._______.   '.   /    (_| .')		 |______|
  '._____.  /   '-/      | _.' 
   '.______ (         ) ) \
     '..____ '._       )  )
        .' __.--\  , ,  // ((
        '.'     |  \/   (_.'(  
                '   \ .' 
                 \   (
                  \   '.
                   \ \ '.)
                    '-'-'



)";


			write_to_storefront(store);
			write_to_user_info(users);

			//CLEAN UP
			for (int i = 0; i < store.size(); i++) {
				delete store[i];
			}
			//clean up is unecessary for users because it doesnt use new
			return 0;
		}
		default:
			std::cout<< "Command not recognized. Please try again." << std::endl << std::endl;
		}
	}


	//login current_user;
		//std::cout << "Do you currently have an account? Y/y or N/n: ";
		//std::string account_confirm;
		//std::getline(std::cin, account_confirm);
		//if (account_confirm == "Y" || account_confirm == "y") {
		//	current_user = enter_username(users);
		//}
		//else if (account_confirm == "N" || account_confirm == "n") {
		//	std::cout << "Okay, would you like to create an account? ";
		//	std::string confirm;
		//	std::getline(std::cin, confirm);
		//	if (confirm == "Y" || confirm == "y") {
		//		create_account(users);
		//		current_user = enter_username(users);
		//	}
		//	else if (confirm == "N" || confirm == "n") {
		//		std::cout << "Okay! Enjoy your visit!" << std::endl;
		//		current_user = login("Default", "qqqqqq", 'N');
		//	}
		//}
		//else {
		//	std::cout << "I couldn't get that, please try again another time.";	//make this a function so this line changes to 'please input a valid character' or something
		//}

	//if (current_user.get_is_admin() == 'C') {//if its one of us, prints out all user info. we can be trusted...maybe (:
		//	std::cout << "Now printing all user info for super admin level:" << std::endl;
		//	for (int i = 0; i < users.size(); i++) {
		//		if (users[i].get_is_admin() != 'C') {
		//			std::cout << "Username: " << users[i].get_user() << " | Password: " << users[i].get_password() << std::endl;
		//		}
		//	}
		//}
		////asks to print out storefront. eventually this will be a function
		//std::cout << "Would you like to print out the store's current inventory? Y or N please. ";
		//std::string confirm;
		//std::getline(std::cin, confirm);
		//if (confirm == "Y") {
		//	for (int i = 0; i < store.size(); i++) {
		//		store[i]->print();
		//	}
		//}
		//else if (confirm == "N") {
		//	if (current_user.get_user() == "Default") {
		//		std::cout << "Alright. Take care." << std::endl;
		//	}
		//	else {
		//		std::cout << "Alright. Take care, " << current_user.get_user() << std::endl;
		//	}
		//}
		//else {
		//	std::cout << "I didn't quite get that. Please try again later.";
		//}
		//updates the files, in case data has been changed
	
}
