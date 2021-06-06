#pragma once

#include <iostream>
#include "./AuthController.h"
#include "./SongController.h"
#include "./PlaylistController.h"
#include "./SearchController.h"
#include "./../User.h"
#include "./../Console.h"

class MenuController
{
public:
	static void showOptions()
	{
		Console::clear();

		if (User::isLoggedIn()) {
			MenuController::showLoggedInOptions();
		}
		else {
			MenuController::showGuestOptions();
		}
	}

	static int processInput()
	{
		int input;

		std::cin >> input;

		if (User::isLoggedIn()) {
			MenuController::processLoggedInInput(input);
		}
		else {
			MenuController::processGuestInput(input);
		}

		return input;
	}

	static void processGuestInput(int input)
	{
		switch (input) {
		case 0:
			break;
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

	static void processLoggedInInput(int input)
	{
		switch (input) {
		case 0:
			break;
		case 1:
			SongController::add();
			break;
		case 2:
			PlaylistController::add();
			break;
		case 3:
			PlaylistController::showMyPlaylists();
			break;
		case 4:
			SearchController::search();
			break;
		case 5:
			AuthController::logout();
			break;
		default:
			std::cout << "Invalid choice" << std::endl;
			break;
		}
	}

protected:
	static void showLoggedInOptions()
	{
		std::cout << "Welcome to Playlish, " << User::get("name") << std::endl << std::endl;

		std::cout << "1. Add Song" << std::endl;
		std::cout << "2. Add Playlist" << std::endl;
		std::cout << "3. My Playlists" << std::endl;
		std::cout << "4. Search" << std::endl;
		std::cout << "5. Logout" << std::endl;
		std::cout << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << std::endl;
		std::cout << "Your choice: ";
	}

	static void showGuestOptions()
	{
		std::cout << "Welcome to Playlish" << std::endl << std::endl;

		std::cout << "1. Login" << std::endl;
		std::cout << "2. Create an account" << std::endl;
		std::cout << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << std::endl;
		std::cout << "Your choice: ";
	}
};

