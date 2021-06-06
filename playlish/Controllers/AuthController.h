#pragma once

#include <string>


class AuthController
{
public:
	static void handleSignUp();

	static void handleSignIn();

	static void logout();

	AuthController() { }

protected:
	std::string email;
	std::string username;
	std::string password;
	std::string passwordConfirmation;

	void showInitialMessage() const;

	void promptSignUpInput();

	void signUp() const;

	bool userExists() const;

	int insertUser() const;

	bool validateSignUpInput() const;

	void promptSignInInput();

	void signIn() const;

	bool validateSignInInput() const;
};

