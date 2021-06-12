#pragma once
#include <stdio.h>  
#include <SQLAPI.h>
#include <vector>
#include "./Config.h"

using std::vector;

class DB
{
public:
    DB(DB const&) = delete;
    void operator=(DB const&) = delete;
    SAConnection connection;

    static DB& getInstance()
    {
        static DB instance;
        return instance;
    }

    static SAConnection& conn()
    {
        return DB::getInstance().connection;
    }
private:   

    DB() {
        try {
            vector<string> credentials = Config::getDbCredentials();
            connection.Connect(_TSA(credentials[0].c_str()), _TSA(credentials[1].c_str()), _TSA(credentials[2].c_str()), SA_SQLServer_Client);
        }
        catch (SAException& x) {
            connection.Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
        }
    }
};