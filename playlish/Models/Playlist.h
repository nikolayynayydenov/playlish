#pragma once
#include <iostream>

using std::string;

class Playlist
{
public:
	void promptInput();
	void insertToDb();
	bool validateAddInput() const;
	void attachToUser(long playlistId) const;
protected:
	std::string playlistName;
	int id;
};

