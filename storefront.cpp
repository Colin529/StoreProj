#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

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

		for (int i=0; i<get_line_count(path)-1; i++) {
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
		//throw std::exception("Failed to read from designated file");
	}
	return users;
}

void write_to_userbase(std::vector<login> users, const std::string path) {

	std::ofstream output;
	
	output.open(path);
		if (output.is_open()) {
				output << "username,password,admin" << std::endl;
				for (int i = 0; i < users.size(); i++) {
					output << users[i].get_user() << "," << users[i].get_password() << "," << users[i].get_is_admin() << std::endl;
				}
		}
		else {
				std::cout << "Failed to write to file" << std::endl;
		}
	
	output.close();
}


int main() {
	const std::string PROD_PATH = "Data/products.csv";
	int file_length = get_line_count(PROD_PATH)-1;

	const std::string USER_INFO = "Data/userinfo.csv";
	int user_count = get_line_count(USER_INFO) - 1;

	std::vector<login> users = read_userinfo(USER_INFO);

	product** storefront = read_storefront(PROD_PATH, file_length);

	std::string action_str;
	char action;
	bool flag = false;

	//username and signup loop
	do {
		std::cout << "--WELCOME--" << std::endl;
		std::cout << "Enter 'l' to login,'s' to signup, or 'q' to quit the application" << std::endl;
		std::cout << "Enter Command: ";
		std::getline(std::cin, action_str);
		action = action_str[0];

		std::string username;
		std::string password;
		switch (action) {
		case 'l':
			std::cout << "--LOGIN--" << std::endl;
			std::cout << "Enter Username: ";
			std::getline(std::cin, username);
			std::cout << "Enter Password: ";
			std::getline(std::cin, password);
			
			for (int i = 0; i < user_count; i++) {
				if (users[i].get_user() == username && users[i].get_password() == password) {
					std::cout << "LOGIN SUCCESSFUL" << std::endl;
					flag = true;
				}
			}

			break;

		case 's': {
			std::cout << "--SIGNUP--" << std::endl;
			std::cout << "Enter Username: ";
			std::getline(std::cin, username);
			std::cout << "Enter Password: ";
			std::getline(std::cin, password);

			login l1(username, password, 0);
			users.push_back(l1);

			flag = true;
			break;
		}
		case 'q':
			std::cout << "EXITING TERMINAL" << std::endl;
		default:
			std::cout << "COMMAND \"" << action << "\" NOT RECONGNIZED" << std::endl;
			break;
		}

	} while (flag != true);

	action_str = action_str.empty();
	action = '\0';

	//Store Loop
	std::cout << "--WELCOME TO THE SHOP--" << std::endl;

	do {
		std::cout << "Enter 'a' to print all products or 'f' to filter products" << std::endl;
		std::cout << "Enter Command: ";
		std::getline(std::cin, action_str);
		action = action_str[0];

		switch (action) {
		case 'a':
			for (int i = 0; i < get_line_count(PROD_PATH) - 1; i++) {
				storefront[i]->print();
			}
			break;

		case 'f':
			std::cout << "AVALIBLE FILTERS" << std::endl;
			std::cout << "Enter 't' to filter by type, 'b' for brand, 'r' for non-reserved, or 'p' to set price range" << std::endl;
			std::cout << "Enter Command: ";
			std::getline(std::cin, action_str);
			action = action_str[0];

			std::string brand_str; //for brand filtering
			std::set<std::string> aval_brands; //for brand filtering
			switch (action) {
			case 't':
				std::cout << "Enter 'h' for hat, 'p' for pants, 's' for shirt, 'k' for socks, or 'u' for underwear" << std::endl;
				std::cout << "Enter Command: ";
				std::getline(std::cin, action_str);
				action = action_str[0];
				if (action == 'h') {
					for (int i = 0; i < get_line_count(PROD_PATH); i++) {
						hat* Hat = dynamic_cast<hat*>(storefront[i]);
						if (Hat) {
							Hat->print();
						}
					}
				}
				else if (action == 'p') {
					for (int i = 0; i < get_line_count(PROD_PATH); i++) {
						pants* Pant = dynamic_cast<pants*>(storefront[i]);
						if (Pant) {
							Pant->print();
						}
					}
				}
				else if (action == 's') {
					for (int i = 0; i < get_line_count(PROD_PATH); i++) {
						shirt* Shirt = dynamic_cast<shirt*>(storefront[i]);
						if (Shirt) {
							Shirt->print();
						}
					}
				}
				else if (action == 'k') {
					for (int i = 0; i < get_line_count(PROD_PATH); i++) {
						socks* Sock = dynamic_cast<socks*>(storefront[i]);
						if (Sock) {
							Sock->print();
						}
					}
				}
				else if (action == 'u') {
					for (int i = 0; i < get_line_count(PROD_PATH); i++) {
						underwear* Underwear = dynamic_cast<underwear*>(storefront[i]);
						if (Underwear) {
							Underwear->print();
						}
					}
				}
				else {
					std::cout << "Error!" << std::endl;
				}
				break;
			case 'b':
				for (int i = 0; i < user_count; i++) {
					aval_brands.insert(storefront[i]->get_brand());
				}
				std::cout << "--FILTER BY BRAND--" << std::endl;
				std::cout << "Avalible Brands: ";
				for (std::string brand : aval_brands) {
					std::cout << brand << ", ";
				}
				std::cout << "Enter the brand you'd like to filter by: ";
				std::getline(std::cin, brand_str);

				for (int i = 0; i < user_count; i++) {
					if (storefront[i]->get_brand() == brand_str) {
						storefront[i]->print();
					}
				}
				break;
			case 'r':
				std::cout << "By Reservation" << std::endl;
				break;
			case 'p':
				double max_price = storefront[0]->get_price();
				double min_price = storefront[0]->get_price();

				std::cout << "--FILTER BY PRICE--" << std::endl;
				for (int i = 0; i < file_length; i++) {
					if (storefront[i]->get_price() < min_price) {
						min_price = storefront[i]->get_price();
					}
					else if (storefront[i]->get_price() > max_price) {
						max_price = storefront[i]->get_price();
					}
				}
				std::cout << "The prices you can filter are between: " << min_price << "-" << max_price << std::endl;
				std::string filter_min_str;
				std::string filter_max_str;
	
				std::cout << "What is the minimum price you'd like to filter? ";
				std::getline(std::cin, filter_min_str);
				double filter_min_price = std::stod(filter_min_str);

				std::cout << "What is the maximum price you'd like to filter? ";
				std::getline(std::cin, filter_max_str);
				double filter_max_price = std::stod(filter_max_str);

				for (int i = 0; i < file_length; i++) {
					if (storefront[i]->get_price() <= filter_max_price && storefront[i]->get_price() >= filter_min_price) {
						storefront[i]->print();
					}
				}

				break;
			}
		}
	}while (action != 'q');


	//CLEAN UP
	for (int i = 0; i < file_length; i++) {
		delete storefront[i];
	}
	//clean up is unecessary for users because it doesnt use new, and the one part that does is deconstructed out of scope
	return 0;
}
