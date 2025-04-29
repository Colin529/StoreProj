#include <string>
#include <iostream>
#include <fstream>

#include "product.h"
#include "shirt.h"
#include "pants.h"

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

//Logging In, Signing Up, and Creating Users
std::vector<std::pair<std::string, std::string>> read_database(const std::string& path){
	std::vector<std::pair<std::string, std::string>> user_database;
	std::ifstream stream;
	stream.open(path);
	
	if(stream.is_open()){
		std::string line;
		std::getline(stream, line); // skip header

		while (std::getline(stream, line)) {
			std::string username, password;
			size_t comma_pos = line.find(',');
			
			if (comma_pos != std::string::npos) {
				username = line.substr(0, comma_pos);
				password = line.substr(comma_pos + 1);
				user_database.push_back(std::make_pair(username, password));
			}
		}
	}
	else{
		std::cout << "FAILED TO OPEN THE FILE!!" << std::endl;
	}

	stream.close();
	return user_database;
}


void create_new_user(std::string new_username, std::string new_password, const std::string& path, int count) {
	std::vector<std::pair<std::string, std::string>> new_user_database = read_database(path); 
	new_user_database.push_back(std::make_pair(new_username, new_password));

	std::ofstream output;
	output.open(path);

	if (output.is_open()) {
		output << "username,password\n";

		for(int i = 0; i < new_user_database.size(); i++){
			output << new_user_database[i].first << "," << new_user_database[i].second << "\n"; 
		}
	}
	else {
		std::cout << "Failed to Write" << std::endl;
	}

	output.close();
}

bool check_login_cred(std::string input_username, std::string input_password, const std::string& path, int count) {
std::ifstream stream;
stream.open(path);

	std::string username;
	std::string password;
	bool success_flag = false;
	if (stream.is_open()) {
		std::string line;
		std::getline(stream, line);
	for (int i = 1; i < count; i++) {
		std::getline(stream, username, ',');
		std::getline(stream, password);
		if(input_username == username && input_password == password){
			success_flag = true;
			break;
		}
	}
	stream.close();
	}
	return success_flag;
}

//Store based read and write
void write() {
	const std::string path = "Data/products.csv";

	std::ofstream output;
	output.open(path);

	if (output.is_open()) {
		output << "Yo, ,Check, ,This, ,Out, ,!" << std::endl;
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

			std::getline(stream, line, ',');
			double num_field_one = std::stod(line);

			std::getline(stream, line);
			double num_field_two = std::stod(line);

			//std::getline(stream, line); //no comma because end of line
			//std::string checked_out = line;
			if (clothing_type == "shirt") {
				storefront[i] = new shirt(clothing_type, brand, price, rating, num_field_one, num_field_two);
			}
			if (clothing_type == "pants") {
				storefront[i] = new pants(clothing_type, brand, price, rating, num_field_one, num_field_two);
			}

		}
		std::cout << "Successfully read storefront data." << std::endl;
		stream.close();

	}

	return storefront;

}




int main() {
	const std::string clothes_path = "Data/products.csv";
	const std::string PATH = "/Users/colin/Desktop/cpp_final/data/user_database.csv";
	int file_length = get_line_count(path);
	
	//User Loop
		std::string action_str;
		char action;
		bool flag = false;		
	do{
		std::cout << "--WELCOME--" << std::endl;
		std::cout << "Enter 'l' to login or 's' to signup" << std::endl;
		std::cout << "Enter Command: ";
		std::getline(std::cin, action_str);
		action = action_str[0];
		
		std::string username;
		std::string password;
		switch(action){
			case 'l':
				std::cout << "Enter Username: ";
				std::getline(std::cin, username);
				std::cout << "Enter Password: ";
				std::getline(std::cin, password);
				if (check_login_cred(username, password, user_path, get_line_count(user_path))) {
					flag = true;
					std::cout << "Login Successful!" << std::endl;
				}
				else{
					flag = false;
					std::cout << "THIS USERNAME AND/OR PASSWORD IS NOT RECOGNIZED!" << std::endl;
				}
				break;
				
			case 's':
				std::cout << "--SIGNUP--\n" << std::endl;
				std::cout << "Enter Username: ";
				std::getline(std::cin, username);
				std::cout << "Enter Password: ";
				std::getline(std::cin, password);
				create_new_user(username, password, user_path, get_line_count(user_path));
				break;
				
			default:
				std::cout << "Sorry I couldn't find the command " << action << std::endl;
				break;
		}
	}while(!(flag)); //Breaks when login or signup is successful

	flag = false;
	action_str.clear();
	action = '\0';
	
	do{
		std::cout << "--WELCOME TO THE STORE FRONT-- \n" << std::endl;
		std::cout << "a - print all products" << std::endl;
		std::cout << "b - filter by brand" << std::endl;
		std::cout << "t - filter by type" << std::endl;
		std::cout << "r - filter non-reserved clothes" << std::endl;
		std::cout << "p - filter by price\n" << std::endl;
		std::cout << "Enter Command: " << std::endl;
		std::getline(std::cin, action_str);
		action = action_str[0];

		switch(action){
			case 'a':
				std::cout << "all prods" << std::endl;
				flag = true;
				break;
			case 'b': 
				std::cout << "brands" << std::endl;
				break;
			case 't':
				std::cout << "type" << std::endl;
				break;
			case 'r':
				std::cout << "non-reserved clothes" << std::endl;
				break;
			case 'p':
				std::cout << "filter by price" << std::endl;
				break;
			default:
				std::cout << "Sorry I couldn't find the command  " << action << std::endl;
				break;
		}

		
	}while(!(flag));


	return 0;
}

	/*product* storefront[6]{
		new shirt("shirt", "Great Value", 38.99, 4.2, 16, 34),
		new pants("shirt", "Target", 38.99, 4.1, 30, 32),
		new shirt("shirt", "New brand", 38.99, 4.2, 16, 34),
		new shirt("shirt", "Other brand", 38.99, 4.2, 16, 34),
		new shirt("shirt", "This joke", 38.99, 4.2, 16, 34),
		new shirt("shirt", "Sucks lol", 38.99, 4.2, 16, 34),
	};*/

	product** storefront = read_storefront(clothes_path, file_length);

	/*for (int i = 0; i < 6; i++) {
		storefront[i]->print();
	}

	for (int i = 0; i < 6; i++) {
		delete storefront[i];
	}*/
	
	return 0;
}
