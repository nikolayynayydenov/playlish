#pragma once

#include <string>
#include "./../Models/UserModel.h"

using std::string;

class AuthController
{
public:
	UserModel* user;

	static void handleSignUp();

	static void handleSignIn();

	static void logout();

	AuthController() : user(new UserModel) { }

	AuthController(const AuthController& other)
	{
		copy(other);
	}

	~AuthController()
	{
		delete user;
	}

	AuthController& operator=(const AuthController& other)
	{
		if (this != &other) {
			erase();
			copy(other);
		}

		return *this;
	}

protected:

	void showInitialMessage() const;

	void promptSignUpInput();

	void signUp() const;

	void promptSignInInput();

	void signIn() const;

	AuthController& copy(const AuthController& other)
	{
		user = other.user;
	}

	void erase()
	{
		delete user;
	}
};

