#pragma once

#include <iostream>
#include "./AuthController.h"

class MenuController
{
public:
	static void showOptions()
	{
		std::cout << "Welcome to Playlish" << std::endl << std::endl;

		// TODO: export options to constant associative array
		std::cout << "1. Login" << std::endl;
		std::cout << "2. Create an account" << std::endl;
		std::cout << std::endl;
		std::cout << "Your choice: ";
	}

	static void processInput()
	{
		int input;

		std::cin >> input;

		switch (input) {
		case 1:
			AuthController::handleSignIn();
			break;
		case 2:
			AuthController::handleSignUp();
			break;
		default:
			std::cout << "Invalid choice" << std::endl;
			break;
		}
	}
};

