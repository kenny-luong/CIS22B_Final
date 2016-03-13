#include <iostream>
#include <string>
#include "employee.h"

void Employee::setUsername(string theName) {
	username = theName;
}

void Employee::setPassword(string thePassword) {
	password = thePassword;
}

string Employee::getUsername() {
	return username;
}

string Employee::getPassword() {
	return password;
}