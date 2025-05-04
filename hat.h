#pragma once
#include "product.h"

class hat : public product {
protected:
	double hat_height = 0;
	double brim_width = 0;

public:
	hat(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, int id, double hat_height, double brim_width);

	double get_hat_height() const;
	double get_brim_width() const;

	void set_hat_height(double hat_height);
	void set_brim_width(double brim_width);

	void print() const override;

};