#include "login.h"

login::login() {

}

login::login(std::string user, std::string password, char is_admin)
{
	set_user(user);
	set_password(password);
	this->is_admin = is_admin;
}

std::string login::get_user() const
{
	return user;
}

std::string login::get_password() const
{
	return password;
}

char login::get_is_admin() const
{
	if (is_admin == 'Y' || is_admin == 'N' || is_admin == 'C') {
		return is_admin;
	}
	else {
		throw std::exception("is_admin must be either Y or N");
		//C is for super admin priviliges, so it's not even mentioned in the exception (yes i know you can see it now please ssshhhh about it <3
	}
}

void login::set_user(std::string user)
{
	if (user.length() >= 3) {
		this->user = user;
	}
	else {
		throw std::exception("Username must be three or more characters");
	}
}

void login::set_password(std::string password)
{
	if (password.length() >= 6) {
		this->password = password;
	}
	else {
		throw std::exception("Password must be 6 or more characters");
	}
}
