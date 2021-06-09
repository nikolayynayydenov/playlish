#pragma once
#include <string>
#include "./Controller.h"

class SongController: public Controller 
{
public:
	static void add();

	SongController();
protected:
	std::string songName;
	int length;
	std::string performer;
	int genreId;

	// add
	void insertToDb();
	void promptAddInput();
	bool validateAddInput() const;
};

