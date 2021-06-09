#include "./AuthController.h"
#include <SQLAPI.h>
#include <iostream>
#include "./../Common/User.h"
#include "./../Common/DB.h"
#include "./MenuController.h"
#include "./../Common/Navigator.h"
#include "./../Common/App.h"

void AuthController::handleSignUp()
{
	AuthController authController;
	authController.showInitialMessage();
	authController.promptSignUpInput();

	if (!authController.validateSignUpInput()) {
		App::setMessage("Invalid input.");
		Navigator::goTo("menu.signUp");
		return;
	}

	try {
		authController.signUp();
		App::setMessage("Successfully signed up. Please sing in.");
		Navigator::goTo("menu.signIn");
	}
	catch (std::exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu");
	}
}

void AuthController::handleSignIn()
{
	AuthController authController;
	authController.showInitialMessage();
	authController.promptSignInInput();
	if (!authController.validateSignInInput()) {
		App::setMessage("Invalid input.");
		Navigator::goTo("menu.signIn");
		return;
	}

	try {
		authController.signIn();
		App::setMessage("Successfully logged in");
		Navigator::goTo("menu");
	}
	catch (std::exception exception) {
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
	std::cout << "Please type in you credentials." << std::endl;
}

void AuthController::promptSignUpInput()
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

void AuthController::signUp() const
{
	int rowsAffected = insertUser();

	if (rowsAffected == 0) {
		throw std::exception("Unable to sign up user.");
	}

}

bool AuthController::userExists() const
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[users] WHERE [name] = :1"));
	select << _TSA(username.c_str());
	select.Execute();

	return select.FetchNext();

}

int AuthController::insertUser() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO users (name, email, password, active_from) VALUES (:1, :2, :3, :4)"));
	insert << _TSA(username.c_str()) << _TSA(email.c_str()) << _TSA(password.c_str()) << _TSA("2021-04-21");
	insert.Execute();

	return insert.RowsAffected();
}

bool AuthController::validateSignUpInput() const
{
	if (userExists()) {
		std::cout << "A user with this username already exists." << std::endl;
		return false;
	}

	return true;
}

void AuthController::promptSignInInput()
{
	std::cout << "Username: ";
	std::cin >> username;

	std::cout << "Password: ";
	std::cin >> password;
}

void AuthController::signIn() const
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[users] WHERE [name] = :1 AND [password] = :2"));
	select << _TSA(username.c_str()) << _TSA(password.c_str());
	select.Execute();

	if (select.FetchNext()) {
		User::login(select);
	}
	else {
		throw std::exception("Invalid username or password");
	}
}

bool AuthController::validateSignInInput() const
{
	return true;
}