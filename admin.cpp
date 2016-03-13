#include "admin.h"

Admin::Admin(string theCode) {
	adminCode = theCode;
	isAdmin = true;
}

void Admin::setAdminCode(string theCode) {
	adminCode = theCode;
}

string Admin::getAdminCode() {
	return adminCode;
}