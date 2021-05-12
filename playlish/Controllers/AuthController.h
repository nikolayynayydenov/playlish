#pragma once

#include <string>

class AuthController
{
public:
	static void handleSignUp()
	{
		AuthController authController;
		authController.showSignUpInitialMessage();
		authController.promptSignUpInput();
		if (authController.validateSignUpInput()) {
			authController.signUp();
		}
	}

	static void handleSignIn()
	{

	}

	AuthController() { }

protected:
	std::string email;
	std::string username;
	std::string password;
	std::string passwordConfirmation;

	void showSignUpInitialMessage()
	{
		std::cout << "Please type in you credentials." << std::endl;
	}

	void promptSignUpInput()
	{
		std::cout << "Email: ";
		std::cin >> email;

		std::cout << "Username: ";
		std::cin >> username;

		std::cout << "Password: ";
		std::cin >> password;

		std::cout << "Confirm password: ";
		std::cin >> passwordConfirmation;
	}

	void signUp()
	{
		std::cout << "Signing up" << username << std::endl;
	}

	// TODO
	bool validateSignUpInput()
	{
		return true;
	}

};

