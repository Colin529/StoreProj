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

			std::getline(stream, line, '|');
			int reserved = std::stoi(line);

			std::getline(stream, line);
			int id = std::stoi(line);

			//i used to think this was 'big' if else, HAHAHAHAHAHA.
				if (clothing_type == "shirt") {
					storefront.push_back(new shirt(clothing_type, brand, price, rating, quantity, reserved, id, num_field_one, num_field_two));
				}
				if (clothing_type == "pants") {
					storefront.push_back(new pants(clothing_type, brand, price, rating, quantity, reserved, id, num_field_one, num_field_two));
				}
				if (clothing_type == "socks") {
					storefront.push_back(new socks(clothing_type, brand, price, rating, quantity, reserved, id, num_field_one, num_field_two));
				}
				if (clothing_type == "underwear") {
					storefront.push_back(new underwear(clothing_type, brand, price, rating, quantity, reserved, id, char_field_one, num_field_two));
				}
				if (clothing_type == "shoes") {
					storefront.push_back(new shoes(clothing_type, brand, price, rating, quantity, reserved, id, num_field_one, num_field_two));
				}
				if (clothing_type == "hat") {
					storefront.push_back(new hat(clothing_type, brand, price, rating, quantity, reserved, id, num_field_one, num_field_two));
				}

				//below lines are for printing for verification
				/*std::cout << clothing_type << ", " <<
					brand << ", " <<
					price << ", " <<
					rating << ", ";
					if (clothing_type == "underwear") { char_field_one; } else {num_field_one;}
					std::cout << ", " <<
					num_field_two << ", " <<
					quantity << "|" << 
					id << std::endl;*/

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
	if (password == "menu") {
		login current_user("None", "aaaaaa", 'N');
		std::cout << std::endl;
		return current_user;
	}
	if (password == user.get_password()) {
		if (user.get_user() == "Karasu" || user.get_user() == "Colin") {
			std::cout << "Welcome, creator " << user.get_user() << "! Have fun :D" << std::endl;
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
	if (username == "menu") {
		login current_user("None", "aaaaaa", 'N');
		std::cout << std::endl;
		return current_user;
	}
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

login create_account(std::vector<login>& users) {
	std::cout << "Please enter the username you want to use. It can't be less than three characters, or more than 20." << std::endl;
	bool valid_username = false;
	bool unique_username = false;
	std::string new_username;
	while (valid_username == false && unique_username==false) {	//continueously checks if the username is valid and unique
		std::getline(std::cin, new_username);
		if (new_username == "menu") {
			login current_user("None", "aaaaaa", 'N');
			std::cout << std::endl;
			return current_user;
		}
		else if (new_username.length() < 3) {
			std::cout << "Your username must be at least 3 characters! Please enter a valid username." << std::endl;
			return create_account(users);
		}
		else {
			valid_username = true;
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
	}
	std::cout << std::endl << "Alright, " << new_username << ", please enter a password. It must be 6-25 characters." << std::endl;
	bool valid_password = false;
	while (valid_password == false) {	//continueously checks if the password is valid
		std::string new_password;
		std::getline(std::cin, new_password);
		if (new_password == "menu") {
			login current_user("None", "aaaaaa", 'N');
			std::cout << std::endl;
			return current_user;
		}
		else if (new_password.length() < 6) {
			std::cout << "Your password must be at least 6 characters! Please enter a valid password." << std::endl;
		}
		else {
			users.push_back(login(new_username, new_password, 'N'));
			std::cout << std::endl << "Awesome! Welcome, " << users[users.size()-1].get_user() << "." << std::endl;
			valid_password = true;
			return users[users.size()-1];
		}
	}
}

void add_product(std::vector<product*> &store, int max_ids[]) {
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
				std::cout << std::endl;
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
				std::cout << std::endl;
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
			std::cout << "What is the rating for the clothes? ";
			std::getline(std::cin, get_rating);
			if (get_rating == "menu") {
				std::cout << std::endl;
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
		std::cout << clothing_type << std::endl;
		if (clothing_type == "shirt") {
			while (field_one < 14 || field_one > 20) {
				std::cout << "What is the collar size? Reminder that it must be between 14-20: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					std::cout << std::endl;
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
			while (field_one < 27 || field_one > 44) {
				std::cout << "What is the waist size? Reminder that it must be between 27-44: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					std::cout << std::endl;
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
			while (field_one < 3 || field_one > 10) {
				std::cout << "What is the sock height? Reminder that it must be between 3-10: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					std::cout << std::endl;
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
					std::cout << std::endl;
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
			while (field_one < 2.5 || field_one > 5) {
				std::cout << "What is the shoe width? Reminder that it must be between 2.5-5: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					std::cout << std::endl;
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
			while (field_one < 3 || field_one > 8) {
				std::cout << "What is the hat height? Reminder that it must be between 3-8: ";
				std::getline(std::cin, get_field_one);
				if (get_field_one == "menu") {
					std::cout << std::endl;
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
			while (field_two < 32 || field_two > 38) {
				std::cout << "What is the sleeve length? Reminder that it must be between 32-38: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					std::cout << std::endl;
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
			while (field_two < 32 || field_two > 51) {
				std::cout << "What is the hip length? Reminder that it must be between 32-51: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					std::cout << std::endl;
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
			while (field_two < 3 || field_two > 14) {
				std::cout << "What is the sock length? Reminder that it must be between 3-14: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					std::cout << std::endl;
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
			while (field_two < 24 || field_two > 40) {
				std::cout << "What is the trunk size? Reminder that it must be between 24-40: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					std::cout << std::endl;
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
			while (field_two < 9 || field_two > 12.5) {
				std::cout << "What is the shoe length? Reminder that it must be between 9-12.5: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					std::cout << std::endl;
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
			while (field_two < 20 || field_two > 25) {
				std::cout << "What is the brim width? Reminder that it must be between 20-25: ";
				std::getline(std::cin, get_field_two);
				if (get_field_two == "menu") {
					std::cout << std::endl;
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
				std::cout << std::endl;
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
			store.push_back(new shirt(clothing_type, brand, price, rating, quantity, 0, max_ids[0]+1, field_one, field_two));
		}
		if (clothing_type == "pants") {
			store.push_back(new pants(clothing_type, brand, price, rating, quantity, 0, max_ids[1]+1, field_one, field_two));
		}
		if (clothing_type == "socks") {
			store.push_back(new socks(clothing_type, brand, price, rating, quantity, 0, max_ids[2]+1, field_one, field_two));
		}
		if (clothing_type == "underwear") {
			store.push_back(new underwear(clothing_type, brand, price, rating, quantity, 0, max_ids[3]+1, underwear_size, field_two));
		}
		if (clothing_type == "shoes") {
			store.push_back(new shoes(clothing_type, brand, price, rating, quantity, 0, max_ids[4]+1, field_one, field_two));
		}
		if (clothing_type == "hat") {
			store.push_back(new hat(clothing_type, brand, price, rating, quantity, 0, max_ids[5]+1, field_one, field_two));
		}
		std::cout << std::endl << std::endl;
		store.at(store.size() - 1)->print();
		std::cout << std::endl <<"Okay! Does this product look correct? Y/y or N/n only, please: ";
		bool valid_yn = false;
		std::string confirm = "a";
		while (valid_yn == false) {
			std::getline(std::cin, confirm);
			if (confirm == "menu") {
				std::cout << std::endl;
				return;
			}
			if (confirm == "y" || confirm == "Y") {
				std::cout << std::endl << "Awesome! Your product has been successfully added to the storefront!" << std::endl << std::endl;
				valid_yn = true;
			}
			else if (confirm == "n" || confirm == "N") {
				std::cout << std::endl << std::endl << "Okay, I'll delete the product. Would you like to try to add a new product? ";
				store.pop_back();
				std::getline(std::cin, confirm);
				if (confirm == "menu") {
					std::cout << std::endl;
					return;
				}
				if (confirm == "y" || confirm == "Y") {
					std::cout << std::endl << std::endl << "Alright, let's take it from the top!" << std::endl << std::endl;
					valid_yn = true;
					return add_product(store, max_ids);
				}
				else if (confirm == "n" || confirm == "N") {
					std::cout << std::endl << std::endl << "Okay, no worries." << std::endl << std::endl;
					valid_yn = true;
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
		std::cout << std::endl;
		return;
	}
	else {
		std::cout << "Please input 'shirt', 'pants', 'socks', 'underwear', 'shoes', or 'hat'!" << std::endl;
		return add_product(store, max_ids);
	}
}

void buy_product(std::vector<product*>& store, std::vector<product*>& buy_from, int buy_from_position) {
	buy_from[buy_from_position]->print();
	int main_store_size = store.size();
	int sub_store_size = buy_from.size();
	std::cout << std::endl << "Alright! Would you like to purchase this product? It will cost $" << buy_from[buy_from_position]->get_price() << ". Type YES to confirm your purchase: ";
	std::string confirm;
	std::getline(std::cin, confirm);
	if (confirm == "menu") {
		std::cout << std::endl;
		return;
	}
	else if (confirm == "YES") {
		for (int i = 0; i < store.size(); i++) {
			if (store[i]->get_id() == buy_from[buy_from_position]->get_id()) {
				int new_quantity = store[i]->get_quantity() - 1;
				store[i]->set_quantity(new_quantity);
				std::cout << std::endl << std::endl << "Awesome! Your purchase was successful. Congratulations on your new " << store[i]->get_clothing_type() << "!" << std::endl << std::endl;
				return;
			}
		}
		std::cout << "Something went wrong...Your purchase has been cancelled." << std::endl << std::endl;
	}
	else if (confirm == "Yes" || confirm == "yes") {
		std::cout << std::endl << "Hmm, it looks like you /do/ want to buy this, but I need CAPS for confirmation. Therefore...Would you like to buy this product? ";
		std::getline(std::cin, confirm);
		if (confirm == "menu") {
			std::cout << std::endl;
			return;
		}
		else if (confirm == "YES") {
			for (int i = 0; i < store.size(); i++) {
				if (store[i]->get_id() == buy_from[buy_from_position]->get_id()) {
					int new_quantity = store[i]->get_quantity() - 1;
					store[i]->set_quantity(new_quantity);
					std::cout << std::endl << std::endl << "Awesome! Your purchase was successful. Congratulations on your new " << store[i]->get_clothing_type() << "!" << std::endl << std::endl;
					return;
				}
			}
			std::cout << "Something went wrong...Your purchase has been cancelled." << std::endl << std::endl;
		}
		else if (confirm == "Yes" || confirm == "yes") {
			std::cout << std::endl << "Alright, it looks like you're not playing along. Purchase has been cancelled." << std::endl << std::endl;
			return;
		}
		else if (confirm == "NO" || confirm == "no" || confirm == "No" || confirm == "N" || confirm == "n") {
			std::cout << std::endl << "Okay! Cancelling purchase." << std::endl << std::endl;
			return;
		}
		else {
			std::cout << std::endl << "I didn't quite get that. Cancelling purchase." << std::endl << std::endl;
			return;
		}
	}
	else if (confirm == "NO" || confirm == "no" || confirm == "No" || confirm == "N" || confirm == "n") {
		std::cout << std::endl << "Okay! Cancelling purchase." << std::endl << std::endl;
		return;
	}
	else {
		std::cout << std::endl << "I didn't quite get that. Would you like to purchase this product? Type YES to confirm your purchase: ";
		std::getline(std::cin, confirm);
		if (confirm == "menu") {
			std::cout << std::endl;
			return;
		}
		else if (confirm == "YES") {
			for (int i = 0; i < store.size(); i++) {
				if (store[i]->get_id() == buy_from[buy_from_position]->get_id()) {
					int new_quantity = store[i]->get_quantity() - 1;
					store[i]->set_quantity(new_quantity);
					std::cout << std::endl << std::endl << "Awesome! Your purchase was successful. Congratulations on your new " << store[i]->get_clothing_type() << "!" << std::endl << std::endl;
					return;
				}
			}
			std::cout << "Something went wrong...Your purchase has been cancelled." << std::endl << std::endl;
		}
		else if (confirm == "Yes" || confirm == "yes") {
			std::cout << std::endl << "Hmm, it looks like you /do/ want to buy this, but I need CAPS for confirmation. Therefore...Would you like to buy this product? ";
			std::getline(std::cin, confirm);
			if (confirm == "menu") {
				std::cout << std::endl;
				return;
			}
			else if (confirm == "YES") {
				for (int i = 0; i < main_store_size; i++) {
					if (store[i]->get_id() == buy_from[buy_from_position]->get_id()) {
						int new_quantity = store[i]->get_quantity() - 1;
						store[i]->set_quantity(new_quantity);
						std::cout << std::endl << std::endl << "Awesome! Your purchase was successful. Congratulations on your new " << store[i]->get_clothing_type() << "!" << std::endl << std::endl;
						return;
					}
				}
				std::cout << "Something went wrong...Your purchase has been cancelled." << std::endl << std::endl;
			}
			else if (confirm == "Yes" || confirm == "yes") {
				std::cout << std::endl << "Alright, it looks like you're not playing along. Purchase has been cancelled." << std::endl << std::endl;
				return;
			}
			else if (confirm == "NO" || confirm == "no" || confirm == "No" || confirm == "N" || confirm == "n") {
				std::cout << std::endl << "Okay! Cancelling purchase." << std::endl << std::endl;
				return;
			}
			else {
				std::cout << std::endl << "I didn't quite get that. Cancelling purchase." << std::endl << std::endl;
				return;
			}
		}
		else if (confirm == "NO" || confirm == "no" || confirm == "No" || confirm == "N" || confirm == "n") {
			std::cout << std::endl << "Okay! Cancelling purchase." << std::endl << std::endl;
			return;
		}
		else {
			std::cout << std::endl << "I didn't quite get that. Cancelling purchase." << std::endl << std::endl;
			return;
		}
	}
}

void edit_product(std::vector<product*>& store) {
	std::string get_value;
	double value = 0;
	char underwear_size = 'a';
	char valid_char = 'a';

	std::cout << std::endl;
	for (int i = 0; i < store.size(); i++) {
		store[i]->print();
	}
	std::cout << std::endl;
	std::cout << "Which product do you want to alter? Reminder to specify via the four digit ID on the right: ";
	int id = 0;
	std::string get_id;
	std::getline(std::cin, get_id);
	if (std::all_of(get_id.begin(), get_id.end(), std::isdigit)) {
		id = stoi(get_id);
	}
	else {
		std::cout << std::endl << "I didn't quite get that. Reminder that the ID will be a four digit code. Please enter the product's ID code: ";
		std::getline(std::cin, get_id);
		if (std::all_of(get_id.begin(), get_id.end(), std::isdigit)) {
			id = stoi(get_id);
		}
		else {
			std::cout << std::endl << "I didn't quite get that. Exiting to main menu." << std::endl << std::endl;
			return;
		}
	}
	if (id >= 1000 && id < 10000) {
		int i = 0;
		while (i < store.size()) {
			if (store[i]->get_id() == id) {
				product* triggered_product = store[i];
				triggered_product->print();
			}
			i++;
		}
		if (i !=store.size()) {
			std::cout << std::endl;
			std::cout << "Alright, let's edit this product! What field do you want to edit?" << std::endl;
			//Start editing fields
			char command = 'a';
			while (command !='M') {
				std::cout << "B for brand, P for price, S for rating, Q for quantity, R for reserved, 1 for the first size field, 2 for the second size field, m when you're done: ";
				std::string get_command;
				std::getline(std::cin, get_command);
				if (get_command == "menu") {
					return;
				}
				std::transform(get_command.begin(), get_command.end(), get_command.begin(), ::toupper);	//this turns all lowercase to uppercase
				command = get_command[0];
				std::cout << std::endl;
				if (command == 'B'){
					std::cout << "Okay! Please set the new brand name. Reminder that the brand must be between 3 and 20 characters: ";
					while (get_value.length()<3||get_value.length()>20) {
						std::getline(std::cin, get_value);
						if (get_value == "menu") {
							std::cout << std::endl;
							return;
						}
						if (get_value.length() < 3 || get_value.length() > 20) {
							std::cout << "Between 3 and 20 characters, please! " << std::endl << std::endl;
						}
					}
					store[i]->set_brand(get_value);
					std::cout << "Alright, the new brand of this product has been set to " << get_value << "." << std::endl << std::endl;
				}
				else if (command == 'P') {
					std::cout << "Okay! Please set the new price. Reminder that the price must be between $10 and $10000: ";
					while (value < 10 || value > 10000) {
						std::getline(std::cin, get_value);
						if (get_value == "menu") {
							std::cout << std::endl;
							return;
						}
						std::istringstream check_string(get_value);
						double check;
						check_string >> std::noskipws >> check;
						if (check_string.eof() && check_string.fail() == false) {
							value = stod(get_value);
							if (value < 10 || value > 10000) {
								std::cout << "10-10000, please! " << std::endl << std::endl;
							}
						}
						else {
							std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
						}
					}
					store[i]->set_price(value);
					std::cout << "Alright, the new price of this product has been set to " << value << "." << std::endl << std::endl;
				}
				else if (command == 'S') {
					std::cout << "Okay! Please set the new rating. Reminder that the rating must be between 0 and 5: ";
					while (value < 0 || value > 5) {
						std::getline(std::cin, get_value);
						if (get_value == "menu") {
							std::cout << std::endl;
							return;
						}
						std::istringstream check_string(get_value);
						double check;
						check_string >> std::noskipws >> check;
						if (check_string.eof() && check_string.fail() == false) {
							value = stod(get_value);
							if (value < 10 || value > 10000) {
								std::cout << "0-5, please! " << std::endl << std::endl;
							}
						}
						else {
							std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
						}
					}
					store[i]->set_quantity(value);
					std::cout << "Alright, the new rating of this product has been set to " << value << "." << std::endl << std::endl;

				}
				else if (command == 'Q') {
					std::cout << "Okay! Please set the new quantity. Reminder that the quantity must be between 0 and 100: ";
					while (value < 0 || value > 100) {
						std::getline(std::cin, get_value);
						if (get_value == "menu") {
							std::cout << std::endl;
							return;
						}
						if (std::all_of(get_value.begin(), get_value.end(), std::isdigit)) {
							value = stoi(get_value);
							if (value < 0 || value > 100) {
								std::cout << "0-100, please! " << std::endl << std::endl;
							}
						}
						else {
							std::cout << "Please input a valid number! Integers only, please. " << std::endl << std::endl;
						}
					}
					store[i]->set_quantity(value);
					std::cout << "Alright, the new quantity of this product has been set to " << value << "." << std::endl << std::endl;
				}
				else if (command == 'R') {
					std::cout << "Okay! Please set the new number of reservations. Reminder that the number of reservations must be between 0 and however many clothes already in stock: ";
					while (value < 0 || value > store[i]->get_quantity()) {
						std::getline(std::cin, get_value);
						if (get_value == "menu") {
							std::cout << std::endl;
							return;
						}
						if (std::all_of(get_value.begin(), get_value.end(), std::isdigit)) {
							value = stoi(get_value);
							if (value < 0 || value > store[i]->get_quantity()) {
								std::cout << "0-" << store[i]->get_quantity() << ", please!" << std::endl << std::endl;
							}
						}
						else {
							std::cout << "Please input a valid number! Integers only, please. " << std::endl << std::endl;
						}
					}
					store[i]->set_reserved(value);
					std::cout << "Alright, the new number of reservations for this product has been set to " << value << "." << std::endl << std::endl;
				}
				else if (command == '1') {
					//field one below
					std::string clothing_type;
					if (shirt* shirtptr = dynamic_cast<shirt*>(store[i])) {
						while (value < 14 || value > 20) {
							std::cout << "What is the collar size? Reminder that it must be between 14-20: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 14 || value > 20) {
									std::cout << "14-20, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						shirtptr->set_collar_size(value);
						store[i] = shirtptr;
						std::cout << "Alright, the new collar size for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (pants* pantsptr = dynamic_cast<pants*>(store[i])) {
						while (value < 27 || value > 44) {
							std::cout << "What is the waist size? Reminder that it must be between 27-44: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 27 || value > 44) {
									std::cout << "27-44, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						pantsptr->set_waist_size(value);
						store[i] = pantsptr;
						std::cout << "Alright, the new waist size for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (socks* socksptr = dynamic_cast<socks*>(store[i])) {
						while (value < 3 || value > 10) {
							std::cout << "What is the sock height? Reminder that it must be between 3-10: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 3 || value > 10) {
									std::cout << "3-10, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						socksptr->set_sock_height(value);
						store[i] = socksptr;
						std::cout << "Alright, the new sock height for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (underwear* underwearptr = dynamic_cast<underwear*>(store[i])) {
						while (underwear_size == 'a') {
							std::cout << "What is the size of the underwear? Reminder to use S/M/L/X only: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							if (get_value.length() == 1) {	//checks to see if the taken string is only one character
								valid_char = get_value[0];
								if (valid_char == 'S' || valid_char == 'M' || valid_char == 'L' || valid_char == 'X') {	//verifies that its a valid underwear size/not just a single digit number
									underwear_size = valid_char;
								}
								else {
									std::cout << "S/M/L/X only, please!" << std::endl << std::endl;
								}
							}
						}
						underwearptr->set_underwear_size(underwear_size);
						store[i] = underwearptr;
						std::cout << "Alright, the new underwear size for this product has been set to " << underwear_size << "." << std::endl << std::endl;
					}
					if (shoes* shoesptr = dynamic_cast<shoes*>(store[i])) {
						while (value < 2.5 || value > 5) {
							std::cout << "What is the shoe width? Reminder that it must be between 2.5-5: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 2.5 || value > 5) {
									std::cout << "2.5-5, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						shoesptr->set_shoe_width(value);
						store[i] = shoesptr;
						std::cout << "Alright, the new shoe width for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (hat* hatptr = dynamic_cast<hat*>(store[i])) {
						while (value < 3 || value > 8) {
							std::cout << "What is the hat height? Reminder that it must be between 3-8: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 3 || value > 8) {
									std::cout << "3-8, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						hatptr->set_hat_height(value);
						store[i] = hatptr;
						std::cout << "Alright, the new hat height for this product has been set to " << value << "." << std::endl << std::endl;
					}
				}
				else if (command == '2') {
					//field two below
					if (shirt* shirtptr = dynamic_cast<shirt*>(store[i])) {
						while (value < 32 || value > 38) {
							std::cout << "What is the sleeve length? Reminder that it must be between 32-38: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 32 || value > 38) {
									std::cout << "32-38, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						shirtptr->set_sleeve_length(value);
						store[i] = shirtptr;
						std::cout << "Alright, the new sleeve length for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (pants* pantsptr = dynamic_cast<pants*>(store[i])) {
						while (value < 32 || value > 51) {
							std::cout << "What is the hip length? Reminder that it must be between 32-51: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 32 || value > 51) {
									std::cout << "32-51, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						pantsptr->set_hip_length(value);
						store[i] = pantsptr;
						std::cout << "Alright, the new hip length for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (socks* socksptr = dynamic_cast<socks*>(store[i])) {
						while (value < 3 || value > 14) {
							std::cout << "What is the sock length? Reminder that it must be between 3-14: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 3 || value > 14) {
									std::cout << "3-14, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							};
						}
						socksptr->set_sock_length(value);
						store[i] = socksptr;
						std::cout << "Alright, the new sock length for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (underwear* underwearptr = dynamic_cast<underwear*>(store[i])) {
						while (value < 24 || value > 40) {
							std::cout << "What is the trunk size? Reminder that it must be between 24-40: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 24 || value > 40) {
									std::cout << "24-40, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						underwearptr->set_trunk_size(value);
						store[i] = underwearptr;
						std::cout << "Alright, the new trunk size for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (shoes* shoesptr = dynamic_cast<shoes*>(store[i])) {
						while (value < 9 || value > 12.5) {
							std::cout << "What is the shoe length? Reminder that it must be between 9-12.5: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 9 || value > 12.5) {
									std::cout << "9-12.5, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						shoesptr->set_shoe_length(value);
						store[i] = shoesptr;
						std::cout << "Alright, the new shoe length for this product has been set to " << value << "." << std::endl << std::endl;
					}
					if (hat* hatptr = dynamic_cast<hat*>(store[i])) {
						while (value < 20 || value > 25) {
							std::cout << "What is the brim width? Reminder that it must be between 20-25: ";
							std::getline(std::cin, get_value);
							if (get_value == "menu") {
								std::cout << std::endl;
								return;
							}
							std::istringstream check_string(get_value);
							double check;
							check_string >> std::noskipws >> check;
							if (check_string.eof() && check_string.fail() == false) {
								value = stod(get_value);
								if (value < 20 || value > 25) {
									std::cout << "20-25, please!" << std::endl << std::endl;
								}
							}
							else {
								std::cout << "Please input a valid number! Integers and Doubles only, please." << std::endl << std::endl;
							}
						}
						hatptr->set_brim_width(value);
						store[i] = hatptr;
						std::cout << "Alright, the new brim width for this product has been set to " << value << "." << std::endl << std::endl;
					}
				}
				else if (command == 'M') {
					std::cout << std::endl << "Okay! Changes have been saved. Returning to the main menu." << std::endl << std::endl;
					return;
				}
				else {
					std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
				}












			}
		}
	}
	else {
		std::cout << std::endl << "Product IDs should be four digits long (e.g. '1234'). Please enter the product's ID code: ";
		std::getline(std::cin, get_id);
		if (std::all_of(get_id.begin(), get_id.end(), std::isdigit)) {
			id = stoi(get_id);
			if (id >= 1000 && id < 10000) {
				int i = 0;
				while (i < store.size()) {
					if (store[i]->get_id() == id) {
						product* triggered_product = store[i];
						triggered_product->print();
					}
					i++;
				}
				if (i != store.size()) {
					std::cout << std::endl;
				}
			}
			else {
				std::cout << std::endl << "I didn't quite get that. Exiting to main menu." << std::endl << std::endl;
				return;
			}
		}
		else {
			std::cout << std::endl << "I didn't quite get that. Exiting to main menu." << std::endl << std::endl;
			return;;
		}
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
			output << store[i]->get_reserved() << '|';
			output << store[i]->get_id();
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

int main() {
	const std::string path = "Data/products.csv";

	const std::string userinfo = "Data/userinfo.csv";

	std::vector<login> users = read_userinfo(userinfo);

	std::vector<product*> store = read_store(path);

	std::vector<product*> shopping_cart;

	int max_shirt_id = 1000;
	int max_pants_id = 2000;
	int max_socks_id = 3000;
	int max_underwear_id = 4000;
	int max_shoes_id = 5000;
	int max_hat_id = 6000;
	std::for_each(store.begin(), store.end(), [&max_shirt_id, &max_pants_id, &max_socks_id, &max_underwear_id, &max_shoes_id, &max_hat_id](product*& p) {
		if (shirt* shirtptr = dynamic_cast<shirt*>(p)) {
			if (p->get_id() > max_shirt_id) {
				max_shirt_id = p->get_id();
			}
		}
		if (pants* pantsptr = dynamic_cast<pants*>(p)) {
			if (p->get_id() > max_pants_id) {
				max_pants_id = p->get_id();
			}
		}
		if (socks* socksptr = dynamic_cast<socks*>(p)) {
			if (p->get_id() > max_socks_id) {
				max_socks_id = p->get_id();
			}
		}
		if (underwear* underwearptr = dynamic_cast<underwear*>(p)) {
			if (p->get_id() > max_underwear_id) {
				max_underwear_id = p->get_id();
			}
		}
		if (shoes* shoesptr = dynamic_cast<shoes*>(p)) {
			if (p->get_id() > max_shoes_id) {
				max_shoes_id = p->get_id();
			}
		}
		if (hat* hatptr = dynamic_cast<hat*>(p)) {
			if (p->get_id() > max_hat_id) {
				max_hat_id = p->get_id();
			}
		}
		});
	int max_ids[6]{max_shirt_id,max_pants_id,max_socks_id,max_underwear_id,max_shoes_id,max_hat_id};

	login current_user("None", "aaaaaa", 'N');

	char command='0';
	//formatting is messy but I promise it looks good on console, otherwise its super broken
	std::cout << std::endl << R"(
			   			 __
			    .-.	                /^{>
			   /'v'\	    ____) (____
			  (/   \)         //'--;   ;--'\\
			 ='="="===<	 ///////\_/\\\\\\\
			    |_|			m m
		|------------------------------------|
		|--Welcome to Crow's Nest Clothing!--|
		|------------------------------------|
		
		
		)" << std::endl << std::endl;

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
			std::cout << "[V/v]: View products in your shopping cart & buy them" << std::endl;
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
			int valid = 0;
			while (valid == 0) {
				std::cout << "Availible filters:" << std::endl;
				std::cout << "[T/t] for clothing type, [B/b] for brand, [S/s] for clothing currently in stock, or [P/p] to set price range: ";
				std::getline(std::cin, get_command);
				if (get_command == "menu") {
					std::cout << std::endl;
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
						std::cout << std::endl;
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
							valid = 1;
							break;
					case 'P':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (pants* print_pants = dynamic_cast<pants*>(p)) {
								print_pants->print();
							}});
							std::cout << std::endl;
							valid = 1;
							break;
					case 'T':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (socks* print_socks = dynamic_cast<socks*>(p)) {
								print_socks->print();
							}});
							std::cout << std::endl;
							valid = 1;
							break;
					case 'U':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (underwear* print_underwear = dynamic_cast<underwear*>(p)) {
								print_underwear->print();
							}});
							std::cout << std::endl;
							valid = 1;
							break;
					case 'V':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (shoes* print_shoes = dynamic_cast<shoes*>(p)) {
								print_shoes->print();
							}});
							std::cout << std::endl;
							valid = 1;
							break;
					case 'H':
						std::for_each(store.begin(), store.end(), [](product*& p) {
							if (hat* print_hat = dynamic_cast<hat*>(p)) {
								print_hat->print();
							}});
							std::cout << std::endl;
							valid = 1;
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
						std::cout << std::endl;
						break;
					}
					std::cout << std::endl;
					std::for_each(store.begin(), store.end(), [&brand_search](product*& p) {
						if (p->get_brand() == brand_search) {
							p->print();
						}
						});
					valid = 1;
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
					valid = 1;
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
							std::cout << std::endl;
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
							std::cout << std::endl;
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
					valid = 1;
					std::cout << std::endl;
					break;
				}
				default:
					std::cout << std::endl << "Please enter a valid character!" << std::endl << std::endl;
				}
			}
				break;
		}
		case 'S'://sort data
		{
			std::string sort_str;
			char sort;

			std::cout << "How would you like to sort the data?" << std::endl;
			std::cout << "[A] Alphabetical (Brand)" << std::endl;
			std::cout << "[P] By Price" << std::endl;
			std::cout << "[Z] By Quantity" << std::endl;
			std::cout << "Enter Command: ";
			std::getline(std::cin, sort_str);
			sort = sort_str[0];

			if (sort == 'A') {
				std::cout << "Alphabetical! [A] Ascending or [D] Desending:";
				std::getline(std::cin, sort_str);
				sort = sort_str[0];
				if (sort == 'A') {//ascending alphabetical order
					std::sort(store.begin(), store.end(), [](const product* a, const product* b) {
						return a->get_brand() < b->get_brand();
						});
				}
				else if (sort == 'D') {//descending alphabetical order
					std::sort(store.begin(), store.end(), [](const product* a, const product* b) {
						return a->get_brand() > b->get_brand();
						});
				}
			}
			else if (sort == 'P') {
				std::cout << "By Price! [A] Ascending or [D] Desending:";
				std::getline(std::cin, sort_str);
				sort = sort_str[0];
				if (sort == 'A') {//ascending order by price
					std::sort(store.begin(), store.end(), [](const product* a, const product* b) {
						return a->get_price() < b->get_price();
						});
				}
				else if (sort == 'D') {//descending order by price
					std::sort(store.begin(), store.end(), [](const product* a, const product* b) {
						return a->get_price() > b->get_price();
						});
				}
			}
			else if (sort == 'Z') {
				std::cout << "By Quantity! [A] Ascending or [D] Desending:";
				std::getline(std::cin, sort_str);
				sort = sort_str[0];
				if (sort == 'A') {//ascending order by quantity
					std::sort(store.begin(), store.end(), [](const product* a, const product* b) {
						return a->get_quantity() < b->get_quantity();
						});
				}
				else if (sort == 'D') {//descending order by quantity
					std::sort(store.begin(), store.end(), [](const product* a, const product* b) {
						return a->get_quantity() > b->get_quantity();
						});
				}
			}

			// Print sorted list
			std::cout << "\nSorted Product List:\n";
			for (int i = 0; i < store.size(); i++) {
				store[i]->print();
			}
			break;
		}
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
		{
			if (current_user.get_user() == "None") {
				current_user = create_account(users);
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		}
		//~~I'm so sorry in advance for the next one, it's not very...legible. If necessary, I can try to comment on it, but...~~
		//NVM figured out an easier way--product IDs work better lol
		case 'B'://buy product (logged in)
		{
			if (current_user.get_user() != "None") {
				//buy product code goes here
				for (int i = 0; i < store.size(); i++) {
					if (store[i]->get_quantity() != 0) {
						store[i]->print();
					}
				}
				std::cout << std::endl << "Please specify which brand you wish to purchase from. If there are multiple pieces of clothing, I'll ask you for some more details." << std::endl;
				std::string brand_search;
				std::getline(std::cin, brand_search);
				if (brand_search == "menu") {
					std::cout << std::endl;
					break;
				}

				else if (brand_search.length() >= 1 && brand_search.length() <= 20) {
					std::vector<product*> buy_from_store;
					int i = 0;
					std::cout << std::endl;
					int size = store.size();
					while (i < size) {
						if (store[i]->get_brand() == brand_search){
							//okay im really mad, i tried just doing the pushback with store[i] but it would throw an error
							//so i fanangled my way to making a two step process and it worked...idk why
							product* triggered_product = store[i];
							buy_from_store.push_back(triggered_product);
							triggered_product->print();
						}
						i++;
					}

					if (buy_from_store.empty()) {
						std::cout << std::endl << "We currently don't have any clothes from " << brand_search << "." <<std::endl << std::endl;
					}
					else {
						std::cout << std::endl << "We found " << buy_from_store.size() << " item";
						if (buy_from_store.size() > 1) {
							std::cout << "s from " << brand_search << "!" << std::endl << std::endl;

							std::cout << "Please enter the product's ID code you wish to buy (located after the '|' at the end of its description): ";
							int id = 0;
							std::string get_id;
							std::getline(std::cin, get_id);
							if (std::all_of(get_id.begin(), get_id.end(), std::isdigit)) {
								id = stoi(get_id);
							}
							else {
								std::cout << std::endl << "I didn't quite get that. Reminder that the ID will be a four digit code. Please enter the product's ID code: ";
								std::getline(std::cin, get_id);
								if (std::all_of(get_id.begin(), get_id.end(), std::isdigit)) {
									id = stoi(get_id);
								}
								else {
									std::cout << std::endl << "I didn't quite get that. Exiting to main menu." << std::endl << std::endl;
									break;
								}
							}
							if (id >= 1000 && id < 10000) {
								int i = 0;
								while (i < size) {
									if (buy_from_store[i]->get_id() == id) {
										product* triggered_product = buy_from_store[i];
										buy_from_store.push_back(triggered_product);
										triggered_product->print();
										break;
									}
									i++;
								}
								if (i > 0) {
									std::cout << std::endl;
									buy_product(store, buy_from_store, i);
								}
							}
							else {
								std::cout << std::endl << "Product IDs should be four digits long (e.g. '1234'). Please enter the product's ID code: ";
								std::getline(std::cin, get_id);
								if (std::all_of(get_id.begin(), get_id.end(), std::isdigit)) {
									id = stoi(get_id);
									if (id >= 1000 && id < 10000) {
										int i = 0;
										while (i < size) {
											if (buy_from_store[i]->get_id() == id) {
												product* triggered_product = buy_from_store[i];
												buy_from_store.push_back(triggered_product);
												triggered_product->print();
												break;
											}
											i++;
										}
										if (i > 0) {
											std::cout << std::endl;
											buy_product(store, buy_from_store, i);
										}
									}
									else {
										std::cout << std::endl << "I didn't quite get that. Exiting to main menu." << std::endl << std::endl;
										break;
									}
								}
								else {
									std::cout << std::endl << "I didn't quite get that. Exiting to main menu." << std::endl << std::endl;
									break;
								}
							}

						
						}
						else {
							std::cout << " from " << brand_search << "!" << std::endl << std::endl;
							buy_product(store, buy_from_store, 0);
						}
					}
				}
				else {
					std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
				}
				break;
			}
		}
		case 'R'://reserve product (logged in)
			if (current_user.get_user() != "None") {
				for (int i = 0; i < store.size(); i++) {
					store[i]->print();
				}
				std::cout << std::endl;
				while (true) {
					std::string product_id_str;
					std::cout << "\nWhich product would you like to add to your cart?" << std::endl;
					std::cout << "Enter product ID Number or [Q] to quit: ";
					std::getline(std::cin, product_id_str);

					if (product_id_str == "q" || product_id_str == "Q") {
						break;
					}


					int prod_id;
					try {
						prod_id = std::stoi(product_id_str);
					}
					catch (...) {
						std::cout << "Invalid input. Please enter a numeric ID or 'Q' to quit." << std::endl;
						continue;
					}


					product* selected_product = nullptr;
					for (int i = 0; i < store.size(); i++) {
						if (store.at(i)->get_id() == prod_id) {
							selected_product = store.at(i);
							break;
						}
					}

					if (selected_product == nullptr) {
						std::cout << "No product found with ID: " << prod_id << std::endl;
						continue; // ask again
					}

					// Ask for confirmation
					std::cout << "\nAdd to cart? Brand: " << selected_product->get_brand()
						<< " | ID: " << selected_product->get_id()
						<< "\nConfirm [Y]es / [N]o: ";
					std::string confirmation_str;
					std::getline(std::cin, confirmation_str);

					if (confirmation_str.empty()) {
						std::cout << "INVALD INPUT.\n";
						continue;
					}

					char confirmation = std::toupper(confirmation_str[0]);

					if (confirmation == 'Y') {
						shopping_cart.push_back(selected_product);
						std::cout << std::endl << "Product added to your cart.\n";
						selected_product->set_reserved(selected_product->get_reserved() + 1);
						break;
					}
					else if (confirmation == 'N') {
						std::cout << std::endl << "PRODUCT NOT ADDED TO YOUR CART \n";
						continue;
					}
					else {
						std::cout << std::endl << "COMMAND NOT RECOGNIZED\n";
						continue;
					}
				}
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'V'://view and buy reserved products (logged in)
			if (current_user.get_user() != "None") {
				if (shopping_cart.empty()) {
					std::cout << "Your shopping cart is empty." << std::endl;
				}
				else {
					std::cout << "--"<< current_user.get_user() << "'s SHOPPING CART--" << std::endl;
					for (int i = 0; i < shopping_cart.size(); i++) {
						shopping_cart.at(i)->print();
					}
					std::cout << std::endl;

					std::cout << "Would you like to purchase something from your cart? Y/y & N/n only: ";
					std::string confirm;
					std::getline(std::cin, confirm);
					if (confirm == "menu") {
						break;
					}
					std::transform(confirm.begin(), confirm.end(), confirm.begin(), ::toupper);
					char confirmation = confirm[0];
					
					if (confirmation == 'Y') {
						while (true) {
							std::string product_id_str;
							std::cout << "\nWhich product would you like to purchase from your cart?" << std::endl;
							std::cout << "Enter product ID Number or [Q] to quit: ";
							std::getline(std::cin, product_id_str);

							if (product_id_str == "q" || product_id_str == "Q") {
								break;
							}


							int prod_id;
							try {
								prod_id = std::stoi(product_id_str);
							}
							catch (...) {
								std::cout << "Invalid input. Please enter a numeric ID or 'Q' to quit." << std::endl;
								continue;
							}

							int i = 0;
							product* selected_product = nullptr;
							for (i; i < store.size(); i++) {
								if (store.at(i)->get_id() == prod_id) {
									selected_product = store.at(i);
									break;
								}
							}

							if (selected_product == nullptr) {
								std::cout << "No product found with ID: " << prod_id << std::endl;
								continue; // ask again
							}
							else {
								buy_product(store, store, i);
								std::vector<product*>::iterator it = shopping_cart.begin();	//takes care of erasing the value and resizing the vector
								int j = 0;
								while (j < shopping_cart.size()) {
									if (shopping_cart[j]->get_id() == prod_id) {
										break;
									}
									if (shopping_cart[j]->get_id() != prod_id) {
										it++;
									}
									j++;
								}
								shopping_cart.erase(it);


								break;
							}
						}
					}
					else if (confirmation == 'N') {
						std::cout << std::endl << "Alright, no worries." << std::endl << std::endl;
					}
					else {

					}

				}
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'A'://add item (admin)
			if (current_user.get_is_admin() == 'Y' || current_user.get_is_admin() == 'C') {
				{
					std::cout << "Alright, let's do this!" << std::endl << std::endl;
					add_product(store, max_ids);
				}
			}
			else {
				std::cout << "Command not recognized. Please try again." << std::endl << std::endl;
			}
			break;
		case 'E'://edit item (admin)
			if (current_user.get_is_admin() == 'Y' || current_user.get_is_admin() == 'C') {
				edit_product(store);
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
				std::cout << std::endl;
				break;
			}
			else if (dlt_account.length() >= 3 && dlt_account.length() <= 20) {
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
							std::cout << std::endl;
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
			write_to_storefront(store);
			write_to_user_info(users);
			std::cout << std::endl << std::endl << "Alright. Thank you for visiting Crow's Nest Clothing! Have a great day ^-^";
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
	//I don't know why this is giving me an error, it compiles perfectly :/
}