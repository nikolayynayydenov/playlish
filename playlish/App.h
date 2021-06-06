#pragma once

#include "./Controllers/MenuController.h"


class App
{
public:
	static void run()
	{
		int input;

		do {
			MenuController::showOptions();
			input = MenuController::processInput();
		} while (input != 0);
	}
};

