#include <iostream>
#include <SQLAPI.h>
#include "./PlaylistSongsController.h"
#include "./SongController.h"
#include "./../Common/DB.h"
#include "./../Common/Navigator.h"
#include "./../Common/App.h"

using std::exception;
using std::cout;
using std::cin;
using std::endl;

void PlaylistSongsController::addSongToPlaylist(int playlistId)
{
	PlaylistSongsController controller;
	controller.playlistId = playlistId;
	controller.promptSongId();

	try {
		controller.attachSongToPlaylist();
		App::setMessage("Song successfully added to playlist");
		Navigator::goTo("menu.playlists.showOwn");
	}
	catch (exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu.playlists.showOwn");
	}
	catch (SAException& exception) {
		App::setMessage("Unable to add song to playlist. It probably already exists in it.");
		Navigator::goTo("menu.playlists.showOwn");
	}
}

void PlaylistSongsController::handleAddSong(int playlistId)
{
   SongController::printAll();
   addSongToPlaylist(playlistId);
}

void PlaylistSongsController::promptSongId()
{
	cout << "Song id: ";
	cin >> songId;
}

void PlaylistSongsController::attachSongToPlaylist() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [playlist_song] (playlist_id, song_id) VALUES (:1, :2)"));
	insert.Param(1).setAsLong() = playlistId;
	insert.Param(2).setAsLong() = songId;

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw exception("Unable to attach song to playlist");
	}
}

void PlaylistSongsController::handleDeleteSong(int playlistId)
{

	PlaylistSongsController controller;
	controller.playlistId = playlistId;
	controller.printPlaylistSongs();
	controller.promptSongId();

	try {
		controller.detachSongFromPlaylist();
		App::setMessage("Song successfully removed from playlist");
		Navigator::goTo("menu.playlists.showOwn");
	}
	catch (exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu.playlists.showOwn");
	}
}

void PlaylistSongsController::printPlaylistSongs() const
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA(
		"SELECT [playlists].* FROM [playlist_song] "
		"INNER JOIN [playlists] ON [playlist_song].[playlist_id] = [playlists].[id] "
		"WHERE[playlist_song].[playlist_id] = :1"
	));

	insert.Param(1).setAsLong() = playlistId;

	insert.Execute();

	int counter = 0;

	while (insert.FetchNext()) {
		cout << insert.Field("id").asString().GetMultiByteChars() << ". " <<
			insert.Field("name").asString().GetMultiByteChars() << endl;

		counter++;
	}

	if (counter == 0) {
		cout << "There are no songs in this playlist.";
	}

	cout << endl;
}

void PlaylistSongsController::detachSongFromPlaylist() const
{
	SAConnection& con = DB::conn();
	SACommand deleteCommand(&con);

	deleteCommand.setCommandText(_TSA("DELETE FROM [playlist_song] WHERE [playlist_id] = :1 AND [song_id] = :2"));
	deleteCommand.Param(1).setAsLong() = playlistId;
	deleteCommand.Param(2).setAsLong() = songId;

	deleteCommand.Execute();

	if (deleteCommand.RowsAffected() == 0) {
		throw exception("Unable to demove song from playlist");
	}
}