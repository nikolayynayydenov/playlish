#pragma once
#include <iostream>
#include <stdlib.h>

#include <SQLAPI.h>
#include <ctime>
#include "PlaylistController.h"
#include "PlaylistSongsController.h"
#include "../Common/Navigator.h"
#include "../Common/DB.h"
#include "../Common/User.h"
#include "GenreController.h"
#include "../Common/Console.h"


class SearchController
{
public:
	static void search();
	

	static void showSearchOptions();
	static void showAfterSearchOptions();
	static bool searchOptionCheck(int);
	static bool afterSearchOptionCheck(int);

	static void processAfterSearchCommand(int);

	static void choosePlaylist();
	
	static void addSongToPlaylist(int);

	static void showUserPlaylists();
	
	static void executeSearchCommand(int);


	//Search options
	static SACommand* searchSongByName(std::string);
	static SACommand* searchSongByPerformer(std::string);
	static SACommand* searchSongByGenre(int);

	static bool useResultOfSearch(SACommand*);


	inline static SACommand* data;

};
