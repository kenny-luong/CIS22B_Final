#ifndef ADMIN_H_INCLUDED
#define ADMIN_H_INCLUDED

#include <iostream>
#include <string>
#include "employee.h"

class Admin : public Employee {
protected:
	bool isAdmin;
	string adminCode;
public:
    Admin() {
        isAdmin = true;
        adminCode = "MISSING";
    }
	Admin(string);
	void setAdminCode(string);
	string getAdminCode();
};

#endif
