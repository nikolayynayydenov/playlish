#include <iostream>
#include <SQLAPI.h>
#include "./SongController.h"
#include "./GenreController.h"
#include "./../Common/DB.h"
#include "./../Common/App.h"
#include "./../Common/Navigator.h"

using std::cout;
using std::endl;

void SongController::printAll()
{
	SAConnection& con = DB::conn();
	SACommand select(&con);

	select.setCommandText(_TSA("SELECT * FROM [songs]"));

	select.Execute();

	int counter = 0;

	cout << endl << "All songs: " << endl << endl;

	while (select.FetchNext()) {
		cout << select.Field(_TSA("id")).asString().GetMultiByteChars() << ". " << select.Field(_TSA("name")).asString().GetMultiByteChars() << endl;
		counter++;
	}

	if (counter == 0) {
		cout << "No songs found" << endl;
	}
}

void SongController::add()
{
	SongController songController;
	songController.promptAddInput();

	if (!songController.validateAddInput()) {
		App::setMessage("Invalid input");
		Navigator::goTo("menu.songs.add");
		return;
	}

	try {
		songController.insertToDb();
		App::setMessage("Successfully added song.");
		Navigator::goTo("menu");
	}
	catch (std::exception exception) {
		App::setMessage(exception.what());
		Navigator::goTo("menu.songs");
	}	
}

void SongController::insertToDb()
{
	SAConnection& con = DB::conn();
	SACommand insert(&con);

	insert.setCommandText(_TSA("INSERT INTO [playlish].[dbo].[songs] (name, length, performer, genre_id) VALUES (:1, :2, :3, :4)"));
	insert.Param(1).setAsString() = _TSA(songName.c_str());
	insert.Param(2).setAsLong() = length;
	insert.Param(3).setAsString() = _TSA(performer.c_str());
	insert.Param(4).setAsLong() = genreId;

	insert.Execute();

	if (insert.RowsAffected() == 0) {
		throw std::exception("Unable to insert song");
	}
}

void SongController::promptAddInput()
{
	std::cout << "Name: ";
	std::cin >> songName;

	std::cout << "Length: ";
	std::cin >> length;

	std::cout << "Performer: ";
	std::cin >> performer;


	GenreController::showAllAsInputOptions();	

	std::cout << "Genre id: " << std::endl << std::endl;
	std::cin >> genreId;

}

bool SongController::validateAddInput() const
{
	return true;
}

void SongController::printFromCommand(SACommand& insert)
{
	if (insert.Field("songName").asString().GetMultiByteCharsLength() != 0) {
		// songName is not null
		cout << "Songs: " << endl << endl;

		do {
			cout << insert.Field("song_id").asLong() << ". " << insert.Field("songName").asString().GetMultiByteChars() <<
				" (" << insert.Field("length").asLong() << ")" << endl;
		} while (insert.FetchNext());

		cout << endl;
	}
	else {
		cout << "No songs here yet" << endl << endl;
	}
}