#ifndef EMPLOYEE_H_INCLUDED
#define EMPLOYEE_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Employee {
protected:
	string username;
	string password;
public:
	void setUsername(string);
	void setPassword(string);
	string getUsername();
	string getPassword();
};

#endif
