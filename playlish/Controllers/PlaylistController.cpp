#include "./PlaylistController.h"
#include "./../Common/App.h"
#include "./../Common/Navigator.h"
#include "./../Common/DB.h"
#include <SQLAPI.h>

void PlaylistController::add()
{
	PlaylistController playlistController;
	playlistController.promptAddInput();

	if (!playlistController.validateAddInput()) {
		App::setMessage("Invalid input");
		Navigator::goTo("menu.playlists.add");
		return;
	}

	try {
		playlistController.insertToDb();
		App::setMessage("Successfully added playlist.");
		Navigator::goTo("menu");
	}
	catch (std::exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu.playlists");
	}
}

void PlaylistController::showOwnPlaylists()
{
	std::cout << "Hello from Playlist showOwnPlaylists()" << std::endl;
}

void PlaylistController::insertToDb()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [playlish].[dbo].[playlists] (name, active_from) VALUES (:1, :2)"));
	insert << _TSA(playlistName.c_str()) << _TSA("2021-04-04");

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to insert song");
	}
}

void PlaylistController::promptAddInput()
{
	std::cout << "Playlist name: ";
	std::cin >> playlistName;
}

bool PlaylistController::validateAddInput() const
{
	return true;
}