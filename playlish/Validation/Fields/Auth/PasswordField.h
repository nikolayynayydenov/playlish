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

class PasswordField : public Field<string>
{
public:
	inline static const int MIN_LENGTH = 6;
	inline static const int MAX_LENGTH = 200;

	PasswordField() : Field<string>("Password") {}

	void showError()
	{
		cout << "Password must be between " << MIN_LENGTH <<
			" and " << MAX_LENGTH << " characters long and contain at least one number." << endl;
	}

	bool validate()
	{
		const regex pattern(".*[0-9].*");

		return value.length() >= MIN_LENGTH && 
			value.length() <= MAX_LENGTH &&
			regex_match(value, pattern);
	}
};