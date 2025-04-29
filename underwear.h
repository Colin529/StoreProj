#pragma once
#include "product.h"

class underwear : public product {
protected:
	char underwear_size;
	int trunk_size = 0;

public:
	underwear(std::string clothing_type, std::string brand, double price, double rating, int quantity, char underwear_size, int trunk_size);

	char get_underwear_size() const;
	int get_trunk_size() const;

	void set_underwear_size(char underwear_size);
	void set_trunk_size(int trunk_size);

	void print() const override;

};