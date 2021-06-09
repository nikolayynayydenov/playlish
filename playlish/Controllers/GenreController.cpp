#include "GenreController.h"
#include "./../Common/DB.h"
#include <SQLAPI.h>
#include <iostream>
#include "./../Common/User.h"


void GenreController::showAllAsInputOptions()
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[genres]"));
	select.Execute();

	while (select.FetchNext()) {
		std::cout << select.Field(_TSA("id")).asString().GetMultiByteChars() << ". " << select.Field(_TSA("name")).asString().GetMultiByteChars() << std::endl;
	}
}