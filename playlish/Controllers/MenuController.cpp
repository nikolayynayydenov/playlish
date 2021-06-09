#include <iostream>
#include "./AuthController.h"
#include "./SongController.h"
#include "./PlaylistController.h"
#include "./SearchController.h"
#include "./../Common/User.h"
#include "./MenuController.h"
#include "./../Common/Navigator.h"

void MenuController::handle()
{
	MenuController::showOptions();
	MenuController::processInput();
}

void MenuController::showOptions()
{
	if (User::isLoggedIn()) {
		MenuController::showLoggedInOptions();
	}
	else {
		MenuController::showGuestOptions();
	}
}

int MenuController::processInput()
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

void MenuController::processGuestInput(int input)
{
	switch (input) {
	case 0:
		break;
	case 1:
		Navigator::goTo("menu.signIn");
		break;
	case 2:
		Navigator::goTo("menu.signUp");
		break;
	default:
		std::cout << "Invalid choice" << std::endl;
		break;
	}
}

void MenuController::processLoggedInInput(int input)
{
	switch (input) {
	case 0:
		break;
	case 1:
		Navigator::goTo("menu.songs.add");
		break;
	case 2:
		Navigator::goTo("menu.playlists.add");
		break;
	case 3:
		Navigator::goTo("menu.playlists.showOwn");
		break;
	case 4:
		Navigator::goTo("menu.search");		
		break;
	case 5:
		Navigator::goTo("menu.logout");
		break;
	default:
		std::cout << "Invalid choice" << std::endl;
		break;
	}
}

void MenuController::showLoggedInOptions()
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

void MenuController::showGuestOptions()
{
	std::cout << "Welcome to Playlish" << std::endl << std::endl;

	std::cout << "1. Login" << std::endl;
	std::cout << "2. Create an account" << std::endl;
	std::cout << std::endl;
	std::cout << "0. Exit" << std::endl;
	std::cout << std::endl;
	std::cout << "Your choice: ";
}