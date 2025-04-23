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
	const std::string path = "Data/products.csv";
	int file_length = get_line_count(path);

	/*product* storefront[6]{
		new shirt("shirt", "Great Value", 38.99, 4.2, 16, 34),
		new pants("shirt", "Target", 38.99, 4.1, 30, 32),
		new shirt("shirt", "New brand", 38.99, 4.2, 16, 34),
		new shirt("shirt", "Other brand", 38.99, 4.2, 16, 34),
		new shirt("shirt", "This joke", 38.99, 4.2, 16, 34),
		new shirt("shirt", "Sucks lol", 38.99, 4.2, 16, 34),
	};*/

	product** storefront = read_storefront(path, file_length);

	/*for (int i = 0; i < 6; i++) {
		storefront[i]->print();
	}

	for (int i = 0; i < 6; i++) {
		delete storefront[i];
	}*/
	
	return 0;
}