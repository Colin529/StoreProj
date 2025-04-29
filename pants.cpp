#include "pants.h"

pants::pants(std::string clothing_type, std::string brand, double price, double rating, int quantity, double waist_size, double hip_length) : product(clothing_type, brand, price, rating, quantity)
{
	set_waist_size(waist_size);
	set_hip_length(hip_length);
}

double pants::get_waist_size() const
{
	return waist_size;
}

double pants::get_hip_length() const
{
	return hip_length;
}

void pants::set_waist_size(double waist_size)
{
	if (waist_size >= 27 && waist_size <= 44) {
		this->waist_size = waist_size;
	}
	else {
		throw std::exception("Waist size must be between 27 and 44 inches");
	}
}

void pants::set_hip_length(double hip_length)
{
	if (hip_length >= 32 && hip_length <= 51) {
		this->hip_length = hip_length;
	}
	else {
		throw std::exception("Hip length must be between 32 and 51 inches");
	}
}

void pants::print() const {
	std::cout << "|" << brand << "| Pants with Waist size " << waist_size << "\" and Hip length " << hip_length << "\" for $" << price << " (Rated " << rating << " out of 5 stars) <" << quantity << " left in stock!>" << std::endl;
}