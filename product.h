#pragma once
#include <string>
#include <iostream>

class product {
protected:

	///*enum class clothing_type{
	//	shirt,
	//	pants,
	//	socks,
	//	underwear,
	//	shoes,
	//	hat,

	//};*/

	std::string clothing_type;
	std::string brand;
	double price = 0;
	double rating = 0;
public:
	product();
	product(std::string clothing_type, std::string brand, double price, double rating);

	//ATTEMPT TO IMPLEMENT ENUM AS A GET/SET FUNCTION
	
	std::string get_clothing_type() const;
	std::string get_brand() const;
	double get_price() const;
	double get_rating() const;

	void set_clothing_type(const std::string& clothing_type);
	void set_brand(const std::string& brand);
	void set_price(double price);
	void set_rating(double rating);

	//void print() const; //SET TO VIRTUAL WHEN TESTING ENUMS
	virtual void print() const = 0; //SET TO PURE VIRTUAL WHEN DONE TESTING ENUMS

};