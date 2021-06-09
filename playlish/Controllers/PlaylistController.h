#pragma once

#include <iostream>
#include "./Controller.h"
#include <string>

class PlaylistController : public Controller
{
public:
	static void add();

	static void showOwnPlaylists();

protected:
	std::string playlistName;
	int id;

	// add
	void insertToDb();
	void promptAddInput();
	bool validateAddInput() const;
	void attachToUser(long playlistId) const;

	//show
	void printOwnPlaylists() const;
	void promptPlaylistChoice();
	void displayPlaylistById() const;
};