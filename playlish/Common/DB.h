#pragma once
#include <stdio.h>  
#include <SQLAPI.h>

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
            connection.Connect(_TSA("DESKTOP-GI5Q4L5\\SQLEXPRESS@playlish"), _TSA("nikolay"), _TSA("querty"), SA_SQLServer_Client);
        }
        catch (SAException& x) {
            connection.Rollback();
            printf("%s\n", x.ErrText().GetMultiByteChars());
        }
    }
};