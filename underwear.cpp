#include "underwear.h"

underwear::underwear(std::string clothing_type, std::string brand, double price, double rating, int quantity, char underwear_size, int trunk_size) : product(clothing_type, brand, price, rating, quantity)
{
	set_underwear_size(underwear_size);
	set_trunk_size(trunk_size);
}

char underwear::get_underwear_size() const
{
	return underwear_size;
}

int underwear::get_trunk_size() const
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

void underwear::set_trunk_size(int trunk_size)
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
	std::cout << "|" << brand << "| Underwear with Size " << underwear_size << " and Trunk size " << trunk_size << "\" for $" << price << " (set of 3) (Rated " << rating << " out of 5 stars) <" << quantity << " left in stock!>" << std::endl;
}
