#pragma once

#include <string>

using std::string;

class AuthController
{
public:
	string email;
	string username;
	string password;
	string passwordConfirmation;

	static void handleSignUp();

	static void handleSignIn();

	static void logout();

	AuthController() : email(""), username(""), password(""), passwordConfirmation("") { }

protected:

	void showInitialMessage() const;

	void promptSignUpInput();

	void signUp() const;

	int insertUser() const;

	void promptSignInInput();

	void signIn() const;
};

