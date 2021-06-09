#pragma once

#include <iostream>
#include "./Controller.h"
#include <string>

class PlaylistController: public Controller
{
public:
	static void add();

	static void showOwnPlaylists();

protected:
	std::string playlistName;

	// add
	void insertToDb();
	void promptAddInput();
	bool validateAddInput() const;
};

