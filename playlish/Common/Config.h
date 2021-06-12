#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::ifstream;
using std::getline;
using std::cout;
using std::exception;

class Config
{
public:
	static vector<string> getDbCredentials()
	{
        ifstream dbConfigFile("db_credentials");
        vector<string> lines;

        if (dbConfigFile.is_open())
        {
            string line;
            while (getline(dbConfigFile, line))
            {
                lines.push_back(line);
            }
            dbConfigFile.close();
        }
        else {
            throw exception("Unable to open db_credentials file.");
        }

        return lines;
	}
};