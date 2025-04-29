#include "hat.h"

hat::hat(std::string clothing_type, std::string brand, double price, double rating, int quantity, double hat_height, double brim_width) : product(clothing_type, brand, price, rating, quantity)
{
	set_hat_height(hat_height);
	set_brim_width(brim_width);
}

double hat::get_hat_height() const
{
	return hat_height;
}

double hat::get_brim_width() const
{
	return brim_width;
}

void hat::set_hat_height(double hat_height)
{
	if (hat_height >= 3 && hat_height <= 8) {
		this->hat_height = hat_height;
	}
	else {
		throw std::exception("Hat height must be between 3 and 8 inches");
	}
}

void hat::set_brim_width(double brim_width)
{
	if (brim_width >= 20 && brim_width <= 25) {
		this->brim_width = brim_width;
	}
	else {
		throw std::exception("Brim width must be between 20 and 25 inches");
	}
}

void hat::print() const
{
	std::cout << "|" << brand << "| Hat with Hat height " << hat_height<< "\" and Brim width " << brim_width << "\" for $" << price << " (Rated " << rating << " out of 5 stars) <" << quantity << " left in stock!>" << std::endl;
}
