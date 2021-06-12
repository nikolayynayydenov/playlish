#pragma once

#include <string>
#include <SQLAPI.h>

#include "./../Common/DB.h"

using std::string;

class UserModel
{
public:
	string email;
	string username;
	string password;
	string passwordConfirmation;

	UserModel() : email(""), username(""), password(""), passwordConfirmation("") { }

	static bool exists(string name)
	{
		SAConnection& con = DB::conn();
		SACommand select(&con);

		select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[users] WHERE [name] = :1"));
		select << _TSA(name.c_str());
		select.Execute();

		return select.FetchNext();
	}

	int insert() const
	{
		SAConnection& con = DB::conn();
		SACommand insert(&con);

		insert.setCommandText(_TSA("INSERT INTO users (name, email, password, active_from) VALUES (:1, :2, :3, :4)"));
		insert << _TSA(username.c_str()) << _TSA(email.c_str()) << _TSA(password.c_str()) << _TSA("2021-04-21");
		insert.Execute();

		return insert.RowsAffected();
	}
};