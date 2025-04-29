#pragma once
#include "product.h"

class shoes : public product {
protected:
	double shoe_width = 0;
	double shoe_length = 0;

public:
	shoes(std::string clothing_type, std::string brand, double price, double rating, int quantity, double shoe_width, double shoe_length);

	double get_shoe_width() const;
	double get_shoe_length() const;

	void set_shoe_width(double shoe_width);
	void set_shoe_length(double shoe_length);

	void print() const override;

};