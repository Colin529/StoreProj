#include "shoes.h"

shoes::shoes(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, int id, double shoe_width, double shoe_length) : product(clothing_type, brand, price, rating, quantity, reserved, id)
{
	set_shoe_width(shoe_width);
	set_shoe_length(shoe_length);
}

double shoes::get_shoe_width() const
{
	return shoe_width;
}

double shoes::get_shoe_length() const
{
	return shoe_length;
}

void shoes::set_shoe_width(double shoe_width)
{

	if (shoe_width >= 2.5 && shoe_width <= 5) {
		this->shoe_width = shoe_width;
	}
	else {
		throw std::exception("Shoe width must be between 2.5 and 5 inches");
	}
}

void shoes::set_shoe_length(double shoe_length)
{
	if (shoe_length >= 9 && shoe_length <= 12.5) {
		this->shoe_length = shoe_length;
	}
	else {
		throw std::exception("Shoe length must be between 9 and 12.5 inches");
	}
}

void shoes::print() const
{
	std::cout << "|" << brand << "| Shoes with Shoe width " << shoe_width << "\" and Shoe length " << shoe_length << "\" for $" << price << " (Rated " << rating << " out of 5 stars) <";

	if (quantity == 0) {
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
