#pragma once

#include <string>
#include <SQLAPI.h>

#include "./../Common/DB.h"

using std::string;

class UserModel
{
public:

	static bool userExists(string name)
	{
		SAConnection& con = DB::conn();
		SACommand select(&con);

		select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[users] WHERE [name] = :1"));
		select << _TSA(name.c_str());
		select.Execute();

		return select.FetchNext();
	}
};