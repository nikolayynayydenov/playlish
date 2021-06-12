#include "Controllers/SearchController.h"



//pause function
void pause(int dur)
{
	int temp = time(NULL) + dur;

	while (temp > time(NULL));
}


void SearchController::search()
{
	std::cout << "SEARCH A SONG: \n" << std::endl;
	SearchController::showSearchOptions();
	int option;
	std::cout << "Please,choose option : \n";
	std::cin >> option;
	if (SearchController::searchOptionCheck(option)) {
	
		SearchController::executeSearchCommand(option);

	}
	else {
		Console::clear();
		std::cout << "Invalid choice \n";
		pause(5);
		SearchController::search();
	}

}

void SearchController::showSearchOptions()
{
	std::cout << "1. search by name. \n";
	std::cout << "2. search by performer. \n";
	std::cout << "3. search by genre. \n";
	std::cout << "0. go back to main menu page. \n";
}

bool SearchController::searchOptionCheck(int user_input)
{
	switch (user_input) {
	case 0:
		return true;
		break;
	case 1:
		return true;
		break;
	case 2:
		return true;
		break;
	case 3:
		return true;
		break;
	default:
		return false;
		break;
	}

}

bool SearchController::afterSearchOptionCheck(int user_input)
{
	switch (user_input) {
	case 0:
		return true;
		break;
	case 1:
		return true;
		break;
	case 2:
		return true;
		break;
	default:
		return false;
		break;
	}
}

void SearchController::processAfterSearchCommand(int command)
{
	switch (command) {
	case 0:
		Navigator::goTo("menu");
		break;
	case 1:
		choosePlaylist();
		  break;
	case 2: 
		Console::clear();
		SearchController::search();
		  break;

	default:
		break;
	}
}

void SearchController::choosePlaylist()
{
	Console::clear();
	std::cout << "Your playlists : \n";
	SearchController::showUserPlaylists();
	int playlist_id;
	std::cout << "Please, choose playlist you want to add a song to it . \n";
	std::cin >> playlist_id;
	SearchController::addSongToPlaylist(playlist_id);
}

void SearchController::executeSearchCommand(int command)
{
	Console::clear();
	switch (command) {
	case 0:
		Navigator::goTo("menu");
		break;
	case 1: {
	std::string path;
	std::cout << "Please, enter song name to search for :\n";
	std::cin >> path;
	if(SearchController::useResultOfSearch(SearchController::searchSongByName(path)))
		SearchController::showAfterSearchOptions();
			else {
					Console::clear();
					std::cout << "No songs found ! \n";
					SearchController::search();
			}
	}
		break;
	case 2: {
		std::string path;
		std::cout << "Please, enter performer name to search for :\n";
		std::cin >> path;
		if (SearchController::useResultOfSearch(SearchController::searchSongByPerformer(path)))
			SearchController::showAfterSearchOptions();
		else {
			Console::clear();
			std::cout << "No songs found ! \n";
			SearchController::search();
		}
	}
		break;

	case 3: {
		int genre;
		GenreController::showAllAsInputOptions();
		std::cout << "Please, enter genre to search for :\n";
		std::cin >> genre;
		Console::clear();
		if (SearchController::useResultOfSearch(SearchController::searchSongByGenre(genre)))
			SearchController::showAfterSearchOptions();
		else {
			Console::clear();
			std::cout << "No songs found ! \n";
			SearchController::search();
		}
	}
		  break;

	default:
		break;
	}

}

SACommand* SearchController::searchSongByName(std::string path)
{
	//connection to DB
	SAConnection& con = DB::conn();
	
	SACommand* select = new SACommand(&con);
	
	(*select).setCommandText(_TSA(
		"SELECT * FROM [songs] "
		
		"WHERE[songs].[name] like " " Concat('%', :1 ,'%') "
		
	));

	(*select) << path.c_str();
	
	//save that data 
	SearchController::data = select;

	return select;
}

SACommand* SearchController::searchSongByPerformer(std::string path)
{
	//connection to DB
	SAConnection& con = DB::conn();

	SACommand* select = new SACommand(&con);

	(*select).setCommandText(_TSA(
		"SELECT * FROM [songs] "

		"WHERE[songs].[performer] like " " Concat('%', :1 ,'%') "

	));

	(*select) << path.c_str();

	//save that data 
	SearchController::data = select;

	return select;
}

SACommand* SearchController::searchSongByGenre(int genre)
{
	//connection to DB
	SAConnection& con = DB::conn();

	SACommand* select = new SACommand(&con);

	(*select).setCommandText(_TSA(
		"SELECT * FROM [songs] "

		"WHERE[songs].[genre_id] = :1 "

	));

	(*select).Param(1).setAsLong() = genre;

	//save that data 
	SearchController::data = select;

	return select;
	
}

void SearchController::addSongToPlaylist(int playlist_id)
{
	Console::clear();
	std::cout << "This was your songs result search : \n ";
	SACommand* data_copy = SearchController::data;
	SearchController::useResultOfSearch(data_copy);
	std::cout << "\n please enter the song id you want to add to your playlist : \n";
	PlaylistSongsController PSC;
	PSC.addSongToPlaylist(playlist_id);
}

void SearchController::showUserPlaylists()
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

	std::cout << "Below are your playlists. " << std::endl << std::endl;;

	int counter = 0;

	while (insert.FetchNext()) {
		std::cout << insert.Field("id").asString().GetMultiByteChars() << ". " <<
			insert.Field("name").asString().GetMultiByteChars() <<std:: endl;

		counter++;
	}

	if (counter == 0) {
		std::cout << "You don't have any playlists yet";
	}
}

void SearchController::showAfterSearchOptions()
{
	std::cout << std::endl << std::endl;
	std::cout << "1. add song to playlist \n";
	std::cout << "2. make new search \n";
	std::cout << "0. go back to main MENU \n";
	int option;

	std::cout << "Please, enter your wish : ";
	std::cin >> option;

	if (SearchController::afterSearchOptionCheck(option)) {
		SearchController::processAfterSearchCommand(option);
	}
	else {
		Console::clear();
		std::cout << "Sorry, invalid input, try again ! \n";
		pause(5); 
		SearchController::showAfterSearchOptions();
	}

}


bool SearchController::useResultOfSearch(SACommand* select)
{
	(*select).Execute();
	int counter = 0;
	while((*select).FetchNext()) {
		std::cout << (*select).Field(_TSA("id")).asString().GetMultiByteChars() << ". " << (*select).Field(_TSA("name")).asString().GetMultiByteChars()
		<<" ,"<< (*select).Field(_TSA("performer")).asString().GetMultiByteChars() << std::endl;
		counter++;
	}

	if (counter == 0) {
		std::cout << "No songs found ! \n";
		return false;
	}

	return true;
}


