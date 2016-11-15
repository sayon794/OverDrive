#pragma once
#include <iostream>
#include <string>

class UserIDMapper {
	std::string userName;
	std::string password;
	std::string rootID;
	std::string Name;

public:
	UserIDMapper() {
		userName = std::string::npos;
		password = std::string::npos;
		rootID = std::string::npos;
		Name = std::string::npos;
	}
	UserIDMapper(std::string un, std::string  pw, std::string  ri, std::string n) {
		userName = un;
		password = pw;
		rootID = ri;
		Name = n;
	}

	std::string getUserName() { return userName; }
	std::string getPassWord() { return password; }
	std::string getRootID() { return rootID; }
	std::string getName() { return Name;  }
};