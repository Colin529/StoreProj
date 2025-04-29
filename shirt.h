#pragma once
#include "product.h"

class shirt : public product {
protected:
	double collar_size = 0;
	double sleeve_length = 0;


public:
	shirt(std::string clothing_type, std::string brand, double price, double rating, int quantity, double collar_size, double sleeve_length);

	double get_collar_size() const;
	double get_sleeve_length() const;

	void set_collar_size(double collar_size);
	void set_sleeve_length(double sleeve_length);

	void print() const override;


};