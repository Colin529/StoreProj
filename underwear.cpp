#include "underwear.h"

underwear::underwear(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, int id, char underwear_size, double trunk_size) : product(clothing_type, brand, price, rating, quantity, reserved, id)
{
	set_underwear_size(underwear_size);
	set_trunk_size(trunk_size);
}

char underwear::get_underwear_size() const
{
	return underwear_size;
}

double underwear::get_trunk_size() const
{
	return trunk_size;
}

void underwear::set_underwear_size(char underwear_size)
{
	if (underwear_size == 'S'|| underwear_size == 'M' || underwear_size == 'L' || underwear_size == 'X') {
		this->underwear_size = underwear_size;
	}
	else {
		throw std::exception("Underwear size must be S, M, L, or X");
	}
}

void underwear::set_trunk_size(double trunk_size)
{
	if (trunk_size >= 24 && trunk_size <= 40) {
		this->trunk_size = trunk_size;
	}
	else {
		throw std::exception("Trunk size must be between 24 and 40 inches");
	}
}

void underwear::print() const
{
	std::cout << "|" << brand << "| Underwear with Size " << underwear_size << " and Trunk size " << trunk_size << "\" for $" << price << " (set of 3) (Rated " << rating << " out of 5 stars) <";

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
