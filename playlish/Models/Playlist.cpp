#include <SQLAPI.h>
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

	insert.setCommandText(_TSA("INSERT INTO [playlish].[dbo].[playlists] (name, active_from) VALUES (:1, :2); SELECT SCOPE_IDENTITY()"));
	insert << _TSA(playlistName.c_str()) << _TSA("2021-04-04");

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