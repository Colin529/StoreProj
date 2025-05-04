#pragma once
#include <string>
#include <iostream>

class product {
protected:
	std::string clothing_type;
	std::string brand;
	double price = 0;
	double rating = 0;
	int quantity = 0;
	int reserved = 0;
	int id = 0;
public:
	product();
	product(std::string clothing_type, std::string brand, double price, double rating, int quantity, int reserved, int id);

	//ATTEMPT TO IMPLEMENT ENUM AS A GET/SET FUNCTION
	
	std::string get_clothing_type() const;
	std::string get_brand() const;
	double get_price() const;
	double get_rating() const;
	int get_quantity() const;
	int get_reserved() const;
	int get_id() const;

	void set_clothing_type(const std::string& clothing_type);
	void set_brand(const std::string& brand);
	void set_price(double price);
	void set_rating(double rating);
	void set_quantity(int quantity);
	void set_reserved(int reserved);

	//void print() const; //SET TO VIRTUAL WHEN TESTING ENUMS
	virtual void print() const = 0; //SET TO PURE VIRTUAL WHEN DONE TESTING ENUMS

};