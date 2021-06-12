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

class EmailField : public Field<string>
{
public:

	EmailField() : Field<string>("Email") {}

	void showError()
	{
		cout << "Email must be in correct format" << endl;
	}

	bool validate()
	{
		const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

		return regex_match(value, pattern);
	}
};