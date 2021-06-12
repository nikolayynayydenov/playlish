#pragma once

#include <string>
#include <iostream>
#include <regex>
#include "./../Field.h"

using std::string;
using std::regex;
using std::regex_match;
using std::cout;
using std::endl;

class PasswordConfirmationField : public Field<string>
{
public:
	PasswordConfirmationField(string password) :
		Field<string>("Confirm password"), password(password) {}

	void showError()
	{
		cout << "The password confirmation must match the password" << endl;
	}

	bool validate()
	{
		return value == password;
	}

protected:
	string password;
};