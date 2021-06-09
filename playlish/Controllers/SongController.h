#pragma once
#include <string>

class SongController
{
public:
	static void add();

	SongController();
private:
	std::string songName;
	int length;
	std::string performer;
	int genreId;

	// add
	void insertToDb();
	void promptAddInput();
	bool validateAddInput() const;
};

