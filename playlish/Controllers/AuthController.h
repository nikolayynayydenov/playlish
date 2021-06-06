#pragma once

#include <SQLAPI.h>
#include <string>
#include <iostream>
#include "./../User.h"
#include "./../DB.h"
#include "./../App.h"
#include "./MenuController.h"

class AuthController
{
public:
	static void handleSignUp()
	{
		AuthController authController;
		authController.showInitialMessage();
		authController.promptSignUpInput();
		if (authController.validateSignUpInput()) {
			authController.signUp();
		}
	}

	static void handleSignIn()
	{
		AuthController authController;
		authController.showInitialMessage();
		authController.promptSignInInput();
		if (authController.validateSignInInput()) {
			authController.signIn();
		}
	}

	static void logout()
	{
		User::logout();
	}

	AuthController() { }

protected:
	std::string email;
	std::string username;
	std::string password;
	std::string passwordConfirmation;

	void showInitialMessage()
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
		int rowsAffected = insertUser();	

		if (rowsAffected > 0) {
			std::cout << "Sign up successful!";
		}
		else {
			std::cout << "Sign up unsuccessful!";
		}
		std::cout << std::endl;

	}

	bool userExists()
	{
		SAConnection& con = DB::conn();
		SACommand select(&con);

		select.setCommandText(_TSA("SELECT * FROM [playlish].[dbo].[users] WHERE [name] = :1"));
		select << _TSA(username.c_str());
		select.Execute();

		return select.FetchNext();

	}

	int insertUser()
	{
		SAConnection& con = DB::conn();
		SACommand insert(&con);

		insert.setCommandText(_TSA("INSERT INTO users (name, email, password, active_from) VALUES (:1, :2, :3, :4)"));
		insert << _TSA(username.c_str()) << _TSA(email.c_str()) << _TSA(password.c_str()) << _TSA("2021-04-21");
		insert.Execute();

		return insert.RowsAffected();
	}

	bool validateSignUpInput()
	{
		if (userExists()) {
			std::cout << "A user with this username already exists." << std::endl;
			return false;
		}

		return true;
	}

	void promptSignInInput()
	{
		std::cout << "Username: ";
		std::cin >> username;

		std::cout << "Password: ";
		std::cin >> password;
	}

	void signIn()
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
			std::cout << "Invalid username or password" << std::endl;
		}
	}	

	bool validateSignInInput()
	{
		return true;
	}
};

