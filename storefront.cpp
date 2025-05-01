#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

//DELETE ALL READ FILE LINES, CAN USE VECTOR .SIZE METHOD


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

			std::getline(stream, line);
			int quantity = std::stoi(line);
			//BIG if else chain, would love to simplify with switch but...doesn't work with string and i dont want to try enum rn...
				if (clothing_type == "shirt") {
					storefront.push_back(new shirt(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two));
				}
				if (clothing_type == "pants") {
					storefront.push_back(new pants(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two));
				}
				if (clothing_type == "socks") {
					storefront.push_back(new socks(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two));
				}
				if (clothing_type == "underwear") {
					storefront.push_back(new underwear(clothing_type, brand, price, rating, quantity, char_field_one, num_field_two));
				}
				if (clothing_type == "shoes") {
					storefront.push_back(new shoes(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two));
				}
				if (clothing_type == "hat") {
					storefront.push_back(new hat(clothing_type, brand, price, rating, quantity, num_field_one, num_field_two));
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
		std::cout << "Successfully read storefront data." << std::endl;
		stream.close();

	}
	else {	//throws exception to stop program from breaking without a correct file
		std::cout << "Failed to read from file--aborting proccess!";
		throw std::exception("Failed to read from designated file");
	}
	return storefront;
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
		
		std::cout << "Successfully read user information." << std::endl;
		stream.close();
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
			output << users[i].get_password() << ",";
			output << users[i].get_is_admin();
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
	//asks for login info, if no, asks for account creation. make this a function maybe?
	login current_user;
	std::cout << "Do you currently have an account? Y/y or N/n: ";
	std::string account_confirm;
	std::getline(std::cin, account_confirm);
	if (account_confirm == "Y" || account_confirm == "y") {
		current_user = enter_username(users);
	}
	else if (account_confirm == "N" || account_confirm == "n") {
		std::cout << "Okay, would you like to create an account? ";
		std::string confirm;
		std::getline(std::cin, confirm);
		if (confirm == "Y" || confirm == "y") {
			create_account(users);
			current_user = enter_username(users);
		}
		else if (confirm == "N" || confirm == "n") {
			std::cout << "Okay! Enjoy your visit!" << std::endl;
			current_user = login("Default", "qqqqqq", 'N');
		}
	}
	else {
		std::cout << "I couldn't get that, please try again another time.";	//make this a function so this line changes to 'please input a valid character' or something
	}

	if (current_user.get_is_admin() == 'C') {//if its one of us, prints out all user info. we can be trusted...maybe (:
		std::cout << "Now printing all user info for super admin level:" << std::endl;
		for (int i = 0; i < users.size(); i++) {
			if (users[i].get_is_admin() != 'C') {
				std::cout << "Username: " << users[i].get_user() << " | Password: " << users[i].get_password() << std::endl;
			}
		}
	}
	//asks to print out storefront. eventually this will be a function
		std::cout << "Would you like to print out the store's current inventory? Y or N please. ";
		std::string confirm;
		std::getline(std::cin, confirm);
		if (confirm == "Y") {
			for (int i = 0; i < store.size(); i++) {
				store[i]->print();
			}
		}
		else if (confirm == "N") {
			if (current_user.get_user() == "Default") {
				std::cout << "Alright. Take care." << std::endl;
			}
			else {
				std::cout << "Alright. Take care, " << current_user.get_user() << std::endl;
			}
		}
		else {
			std::cout << "I didn't quite get that. Please try again later.";
		}
	//updates the files, in case data has been changed
	write_to_storefront(store);
	write_to_user_info(users);

	//CLEAN UP
	for (int i = 0; i < store.size(); i++) {
		delete store[i];
	}
	//clean up is unecessary for users because it doesnt use new
	return 0;
}
