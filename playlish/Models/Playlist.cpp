#include <SQLAPI.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include "./Playlist.h"
#include "./../Common/DB.h"
#include "./../Common/User.h"


using std::cout, std::cin;

void Playlist::promptInput()
{
	cout << "Playlist name: ";
	cin >> playlistName;
}

void Playlist::insertToDb()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	auto time_now = std::chrono::system_clock::now();

	insert.setCommandText(_TSA("INSERT INTO [playlish].[dbo].[playlists] (name, active_from) VALUES (:1, GETDATE()); SELECT SCOPE_IDENTITY()"));
	insert << _TSA(playlistName.c_str());
		
	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to insert playlist");
	}

	insert.FetchNext();

	attachToUser(insert.Field(1).asLong());
}



bool Playlist::validateAddInput() const
{
	return true;
}

void Playlist::attachToUser(long id) const
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