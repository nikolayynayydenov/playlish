#pragma once

#include <iostream>
class PlaylistController
{
public:
	static void add()
	{
		std::cout << "Hello from Playlist add()" << std::endl;
	}

	static void showOwnPlaylists()
	{
		std::cout << "Hello from Playlist showOwnPlaylists()" << std::endl;
	}
};

