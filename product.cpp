#include "product.h"

product::product() {

}


product::product(std::string clothing_type, std::string brand, double price, double rating) {
	set_clothing_type(clothing_type);
	set_brand(brand);
	set_price(price);
	set_rating(rating);

}

//std::string product::get_clothing_type() const
//{
//	return clothing_type;
//}

std::string product::get_clothing_type() const
{
	return clothing_type;
}

std::string product::get_brand() const
{
	return brand;
}

double product::get_price() const
{
	return price;
}

double product::get_rating() const
{
	return rating;
}

void product::set_clothing_type(const std::string& clothing_type)
{
	if (clothing_type == "shirt" || clothing_type == "pants" || clothing_type == "socks" || clothing_type == "underwear" || clothing_type == "shoes" || clothing_type == "hat") {
		this->clothing_type = clothing_type;
	}
	else {
		throw std::exception("Clothing type must be valid (check source information)");
	}
}

void product::set_brand(const std::string& brand)
{
	if (brand.length() > 0) {
		this->brand = brand;
	}
	else {
		throw std::exception("Brand must not be empty");
	}
}

void product::set_price(double price)
{
	if (price > 0 && price < 10000) {
		this->price = price;
	}
	else {
		throw std::exception("Price must be greater than $0 and less than $10,000");
	}
}

void product::set_rating(double rating)
{
	if (rating > 0 && rating < 5) {
		this->rating = rating;
	}
	else {
		throw std::exception("Rating must be between 0 and 5 stars");
	}
}

/*void product::print() const {
	std::cout << "|" << brand << "| " << clothing_type << ": $" << price << " (Rated " << rating << " out of 5 stars)" << std::endl;
}*/