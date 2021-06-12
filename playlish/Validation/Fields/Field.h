#pragma once

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

template <typename T>
class Field
{
public:
	T value;
	string name;

	Field(string name) : name(name) {}

	virtual bool validate() = 0;

	virtual void showError() = 0;

	T prompt()
	{
		bool isValid = false;

		do {
			cout << name << ": ";
			cin >> value;

			isValid = validate();

			if (!isValid) {
				showError();
			}
		} while (!isValid);

		return value;
	}
};