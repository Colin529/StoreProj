#pragma once
#include <string>

class login {
private:
	std::string user;
	std::string password;
	char is_admin;

public:
	login();
	login(std::string user, std::string password, char is_admin);

	std::string get_user() const;
	std::string get_password() const;
	char get_is_admin() const;

	void set_user(std::string user);
	void set_password(std::string password);
};