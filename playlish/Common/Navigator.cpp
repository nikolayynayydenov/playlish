#include "./Navigator.h"
#include "./../Controllers/SongController.h"
#include "./../Controllers/PlaylistController.h"
#include "./../Controllers/SearchController.h"
#include "./App.h"
#include "./../Common/Console.h"

void Navigator::goTo(std::string path) {
	Console::clear();

	App::showMessage();

	if (path == "menu") {
		MenuController::handle();
	}


	// Authentication
	else if (path == "menu.signIn") {
		AuthController::handleSignIn();
	}
	else if (path == "menu.signUp") {
		AuthController::handleSignUp();
	}
	else if (path == "menu.logout") {
		AuthController::logout();
	}


	// Songs
	else if (path == "menu.songs.add") {
		SongController::add();
	}


	// Playlists
	else if (path == "menu.playlists.add") {
		PlaylistController::add();
	}
	else if (path == "menu.playlists.showOwn") {
		PlaylistController::showOwnPlaylists();
	}


	// Search
	else if (path == "menu.search") {
		SearchController::search();
	}


	// Fallback
	else {
		// Invalid path
		std::cout << "Invalid path: " << path << std::endl;
	}
}