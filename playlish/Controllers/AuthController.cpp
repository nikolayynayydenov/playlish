#include <SQLAPI.h>
#include <iostream>
#include <regex>

#include "./AuthController.h"
#include "./MenuController.h"

#include "./../Common/User.h"
#include "./../Common/DB.h"
#include "./../Common/Navigator.h"
#include "./../Common/App.h"

#include "./../Validation/Fields/Auth/UsernameField.h"
#include "./../Validation/Fields/Auth/EmailField.h"
#include "./../Validation/Fields/Auth/PasswordField.h"
#include "./../Validation/Fields/Auth/PasswordConfirmationField.h"

using std::regex;
using std::cout;
using std::cin;
using std::exception;
using std::endl;

void AuthController::handleSignUp()
{
	AuthController authController;
	authController.showInitialMessage();
	authController.promptSignUpInput();

	try {
		authController.signUp();
		App::setMessage("Successfully signed up. Please sing in.");
		Navigator::goTo("menu.signIn");
	}
	catch (exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu");
	}
}

void AuthController::handleSignIn()
{
	AuthController authController;
	authController.showInitialMessage();
	authController.promptSignInInput();

	try {
		authController.signIn();
		App::setMessage("Successfully logged in");
		Navigator::goTo("menu");
	}
	catch (exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu");
	}
}

void AuthController::logout()
{
	User::logout();
	App::setMessage("Logged out");
	Navigator::goTo("menu");
}

void AuthController::showInitialMessage() const
{
	cout << "Please type in you credentials." << endl;
}

void AuthController::promptSignUpInput()
{
	user->username = UsernameField().prompt();

	user->email = EmailField().prompt();

	user->password = PasswordField().prompt();

	user->passwordConfirmation = PasswordConfirmationField(user->password).prompt();
}

void AuthController::signUp() const
{
	int rowsAffected = user->insert();

	if (rowsAffected == 0) {
		throw exception("Unable to sign up user.");
	}

}

void AuthController::promptSignInInput()
{
	user->username = UsernameField().promptForSignIn();

	user->password = PasswordField().prompt();
}

void AuthController::signIn() const
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[users] WHERE [name] = :1 AND [password] = :2"));
	select << _TSA(user->username.c_str()) << _TSA(user->password.c_str());
	select.Execute();

	if (select.FetchNext()) {
		User::login(select);
	}
	else {
		throw exception("Invalid username or password");
	}
}