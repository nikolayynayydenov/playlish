#pragma once

#include <iostream>
#include "./Controller.h"
#include <string>

class PlaylistController
{
public:
	static void add();

	static void showOwnPlaylists();

	PlaylistController() : action(0), id(-1) {}

protected:
	int action;
	int id;

	// show
	void printOwnPlaylists() const;
	void promptPlaylistChoice();
	void displayPlaylistById() const;	

	// delete
	void handleDelete() const;

	// other
	void promptPlaylistAction();
	void handlePlaylistAction();
	
};