#include <SQLAPI.h>

#include "./PlaylistController.h"
#include "./PlaylistSongsController.h"

#include "./../Common/App.h"
#include "./../Common/Navigator.h"
#include "./../Common/DB.h"
#include "./../Common/User.h"
#include "./../Common/Console.h"
#include "./../Models/Playlist.h"

using std::endl;
using std::cout;
using std::cin;

void PlaylistController::add()
{
	Playlist playlist;
	playlist.promptInput();

	if (!playlist.validateAddInput()) {
		App::setMessage("Invalid input");
		Navigator::goTo("menu.playlists.add");
		return;
	}

	try {
		playlist.insertToDb();
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
	playlistController.promptPlaylistAction();
	Console::clear();
	playlistController.handlePlaylistAction();
}

void PlaylistController::printOwnPlaylists() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"SELECT [playlists].* FROM [playlist_user] "
		"INNER JOIN [playlists] ON [playlist_user].[playlist_id] = [playlists].[id] "
		"WHERE[playlist_user].[user_id] = :1"
	));

	insert << User::get("id").c_str();

	insert.Execute();

	cout << "Below are your playlists. Type in an id to view the playlist's songs" << endl << endl;

	while (insert.FetchNext()) {
		cout << insert.Field("id").asString().GetMultiByteChars() << ". " <<
			insert.Field("name").asString().GetMultiByteChars() << endl;
	}
}

void PlaylistController::displayPlaylistById() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"SELECT * FROM [playlists] "
		"LEFT JOIN [playlist_song] ON [playlist_song].[playlist_id] = [playlists].id "
		"LEFT JOIN [songs] ON [playlist_song].[song_id] = [songs].[id] "
		"WHERE [playlists].[id] = :1"
	));

	insert.Param(1).setAsLong() = id;

	insert.Execute();

	if (insert.FetchNext()) {
		cout << "Playlist name: " << insert.Field("name").asString().GetMultiByteChars() << endl;
	}
	else {
		cout << "Playlist was not found." << endl;
	}
}

void PlaylistController::promptPlaylistAction()
{
	cout << "Actions" << endl << endl;

	cout << "1. Add song" << endl;
	cout << "2. Remove song" << endl;
	cout << "3. Delete playlist" << endl;
	cout << "4. Go back" << endl;

	cout << "Action choice: ";
	cin >> action;
}

void PlaylistController::handlePlaylistAction()
{
	while (action == 0) {
		promptPlaylistAction();
	}

	switch (action) {
	case 1:
		PlaylistSongsController::handleAddSong(id);
		break;
	case 2:
		PlaylistSongsController::handleDeleteSong(id);
		break;
	case 3:
		PlaylistController::handleDelete();
		break;
	case 4:
		Navigator::goTo("menu.playlists.showOwn");
		break;
	default:
		break;
	}
}

void PlaylistController::promptPlaylistChoice()
{
	cout << "Choice: ";
	cin >> id;
}

void PlaylistController::handleDelete() const
{

}