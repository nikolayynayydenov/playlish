#include "App.h"
#include <string>
#include <iostream>

void App::setMessage(std::string message)
{
	App::getInstance().message = message;
}

void App::showMessage()
{
	App& app = App::getInstance();

	if (app.message != "") {
		std::cout << App::getInstance().message << std::endl << std::endl;
		app.message = "";
	}
}