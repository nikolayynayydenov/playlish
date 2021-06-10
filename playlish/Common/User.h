#pragma once

#include <SQLAPI.h>
#include <string>
#include <map>

class User
{
public:
	User(User const&) = delete;
	void operator=(User const&) = delete;

	static User& getInstance()
	{
		static User instance;
		return instance;
	}

	static bool isLoggedIn()
	{
		return User::getInstance().isLogged;
	}
	
	static void login(SACommand& selectCommand)
	{
		long colCount = selectCommand.FieldCount();
		User& user = User::getInstance();

		for (int i = 1; i <= colCount; i++)
		{
			user.fields[selectCommand.Field(i).Name().GetMultiByteChars()] = selectCommand.Field(i).asString().GetMultiByteChars();
		}

		user.isLogged = true;
	}

	static void logout()
	{
		User::getInstance().isLogged = false;
	}

	static std::string get(std::string key)
	{
		return User::getInstance().fields[key];
	}

private:
	bool isLogged;
	std::map<std::string, std::string> fields;

	User() :isLogged(false) { }

	static void set(std::string key, std::string value)
	{
		User::getInstance().fields[key] = value;
	}
};
