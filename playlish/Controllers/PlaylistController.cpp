#include "./PlaylistController.h"
#include "./../Common/App.h"
#include "./../Common/Navigator.h"
#include "./../Common/DB.h"
#include "./../Common/User.h"
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
	PlaylistController playlistController;
	playlistController.printOwnPlaylists();
	playlistController.promptPlaylistChoice();
	playlistController.displayPlaylistById();
}

void PlaylistController::printOwnPlaylists() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"SELECT [playlists].* FROM [playlist_user]"
		"INNER JOIN[playlists] ON [playlist_user].[playlist_id] = [playlists].[id]"
		"WHERE[playlist_user].[user_id] = :1"
	));

	insert << User::get("id").c_str();

	insert.Execute();

	std::cout << "Below are your playlists. Type in an id to view the playlist's songs" << std::endl << std::endl;

	while (insert.FetchNext()) {
		std::cout << insert.Field("id").asString().GetMultiByteChars() << ". " <<
					 insert.Field("name").asString().GetMultiByteChars() << std::endl;
	}	
}

void PlaylistController::displayPlaylistById() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"SELECT * FROM[playlists] "
		"LEFT JOIN[playlist_song] ON[playlist_song].[playlist_id] = [playlists].id "
		"LEFT JOIN [songs] ON[playlist_song].[song_id] = [songs].[id] "
		"WHERE[playlists].[id] = :1"
	));

	insert.Param(1).setAsLong() = id;

	insert.Execute();

	if (insert.FetchNext()) {
		std::cout << "Playlist name: " << insert.Field("name").asString().GetMultiByteChars() << std::endl;
		
	}
	else {
		std::cout << "Playlist was not found." << std::endl;
	}
}

void PlaylistController::promptPlaylistChoice() 
{
	std::cout << "Choice: ";
	std::cin >> id;
}

void PlaylistController::insertToDb()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [playlish].[dbo].[playlists] (name, active_from) VALUES (:1, :2); SELECT SCOPE_IDENTITY()"));
	insert << _TSA(playlistName.c_str()) << _TSA("2021-04-04");

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to insert playlist");
	}

	insert.FetchNext();

	attachToUser(insert.Field(1).asLong());
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

void PlaylistController::attachToUser(long id) const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [playlish].[dbo].[playlist_user] (playlist_id, user_id) VALUES (:1, :2)"));
	
	insert.Param(1).setAsLong() = id;
	insert.Param(2).setAsString() = _TSA(User::get("id").c_str());

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to attach playlist");
	}
}