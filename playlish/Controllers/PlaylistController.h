#pragma once

#include <iostream>
class PlaylistController
{
public:
	static void add()
	{
		std::cout << "Hello from Playlist add()" << std::endl;
	}

	static void showMyPlaylists()
	{
		std::cout << "Hello from Playlist showMyPlaylists()" << std::endl;
	}
};

