#pragma once
#include <iostream>
#include <string>

class UserIDMapper {
	std::string userName;
	std::string password;
	std::string rootID;

public:
	UserIDMapper() {
		userName = std::string::npos;
		password = std::string::npos;
		rootID = std::string::npos;
	}
	UserIDMapper(std::string un, std::string  pw, std::string  ri) {
		userName = un;
		password = pw;
		rootID = ri;
	}

	std::string getUserName() { return userName; }
	std::string getPassWord() { return password; }
	std::string getRootID() { return rootID; }
};