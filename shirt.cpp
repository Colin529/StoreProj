#include "shirt.h"

shirt::shirt(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, int id, double collar_size, double sleeve_length) : product(clothing_type, brand, price, rating, quantity, reserved, id) {
	set_collar_size(collar_size);
	set_sleeve_length(sleeve_length);
}

double shirt::get_collar_size() const
{
	return collar_size;
}

double shirt::get_sleeve_length() const
{
	return sleeve_length;
}

void shirt::set_collar_size(double collar_size)
{
	if (collar_size >= 14 && collar_size <= 20) {
		this->collar_size = collar_size;
	}
	else {
		throw std::exception("Collar size must be between 14 and 20 inches");
	}
}

void shirt::set_sleeve_length(double sleeve_length)
{
	if (sleeve_length >= 32 && sleeve_length <= 38) {
		this->sleeve_length = sleeve_length;
	}
	else {
		throw std::exception("Sleeve length must be between 32 and 38 inches");
	}
}

void shirt::print() const {
	std::cout << "|" << brand << "| "
		"Dress Shirt with Collar size " << collar_size <<
		"\" and Sleeve length " << sleeve_length <<
		"\" for $" << price <<
		" (Rated " << rating << " out of 5 stars) <";

		if (quantity==0) {
			std::cout << "Currently out of stock! Please check again another day.> | " << id << std::endl;
		}

		else {
			std::cout << quantity << " left in stock";
			if (reserved == 0) {
				std::cout << ".> | " << id << std::endl;
			}
			else if (reserved == 1) {
				std::cout << ", " << reserved << " of which is in a user's cart!> | " << id << std::endl;
			}
			else {
				std::cout << ", " << reserved << " of which are in users' carts!> | " << id << std::endl;
			}
		}
}