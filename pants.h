#pragma once
#include "product.h"

class pants : public product {
protected:
	double waist_size = 0;
	double hip_length = 0;

public:
	pants(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, double waist_size, double hip_length);

	double get_waist_size() const;
	double get_hip_length() const;

	void set_waist_size(double waist_size);
	void set_hip_length(double hip_length);

	void print() const override;

};