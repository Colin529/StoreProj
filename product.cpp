#include "product.h"

product::product() {

}


product::product(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved) {
	set_clothing_type(clothing_type);
	set_brand(brand);
	set_price(price);
	set_rating(rating);
	set_quantity(quantity);
	set_reserved(reserved);
}

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

int product::get_quantity() const
{
	return quantity;
}

int product::get_reserved() const
{
	return reserved;
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
	if (brand.length() > 0 && brand.length()<=20) {
		this->brand = brand;
	}
	else {
		throw std::exception("Brand must not be empty and be less than 20 characters");
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

void product::set_quantity(int quantity)
{
	if (quantity >= 0 && quantity <= 100) {
		this->quantity = quantity;
	}
	else {
		throw std::exception("Quantity must be between 0 and 100");
	}
}

void product::set_reserved(int reserved)
{
	if (reserved >=0 && reserved <= quantity) {
		this->reserved = reserved;
	}
	else {
		throw std::exception("Reserved field must be between 0 and 100");
	}
}

/*void product::print() const {
	std::cout << "|" << brand << "| " << clothing_type << ": $" << price << " (Rated " << rating << " out of 5 stars)" << std::endl;
}*/