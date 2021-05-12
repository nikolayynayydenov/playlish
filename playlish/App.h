#pragma once

#include "./Controllers/MenuController.h"

class App
{
public:
	static void run()
	{
		MenuController::showOptions();
		MenuController::processInput();
	}
};

