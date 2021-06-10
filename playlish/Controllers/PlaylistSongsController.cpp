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


void PlaylistSongsController::handleAddSong(int playlistId)
{
	SongController::printAll();

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

}