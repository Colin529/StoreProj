#include "socks.h"

socks::socks(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, int id, double sock_height, double sock_length) : product(clothing_type, brand, price, rating, quantity, reserved, id)
{
	set_sock_height(sock_height);
	set_sock_length(sock_length);
}

double socks::get_sock_height() const
{
	return sock_height;
}

double socks::get_sock_length() const
{
	return sock_length;
}

void socks::set_sock_height(double sock_height)
{
	if (sock_height >= 3 && sock_height <= 14) {
		this->sock_height = sock_height;
	}
	else {
		throw std::exception("Sock height must be between 3 and 14 inches");
	}
}

void socks::set_sock_length(double sock_length)
{
	if (sock_length >= 3 && sock_length <= 14) {
		this->sock_length = sock_length;
	}
	else {
		throw std::exception("Sock length must be between 4 and 14 inches");
	}
}

void socks::print() const
{
	std::cout << "|" << brand << "| Socks with Sock height " << sock_height << "\" and Sock length " << sock_length << "\" for $" << price << " (set of 4) (Rated " << rating << " out of 5 stars) <";

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
