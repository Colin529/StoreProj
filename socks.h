#pragma once
#include "product.h"

class socks : public product {
protected:
	double sock_height = 0;
	double sock_length = 0;

public:
	socks(std::string clothing_type, std::string brand, double price, double rating, int quantity, double sock_height, double sock_length);

	double get_sock_height() const;
	double get_sock_length() const;

	void set_sock_height(double sock_height);
	void set_sock_length(double sock_length);

	void print() const override;

};