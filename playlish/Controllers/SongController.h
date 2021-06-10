#pragma once
#include <string>
#include <SQLAPI.h>
#include "./Controller.h"

class SongController : public Controller
{
public:
	static void add();

	static void printAll();

	static void printFromCommand(SACommand&);

	SongController() : songName(""), length(-1), performer(""), genreId(-1) {};
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

